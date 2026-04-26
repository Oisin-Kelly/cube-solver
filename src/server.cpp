#include "CubeSolverLib.hpp"
#include "Face.hpp"
#include "Constants.hpp"
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <fmt/core.h>

using json = nlohmann::json;

static json errorResponse(const std::string &message, const std::string &code)
{
    return {{"error", message},
            {"code", code}};
}

static json okResponse(const std::vector<std::string> &solution, size_t moveCount, long computeTimeUs)
{
    return {{"solution", solution},
            {"moveCount", moveCount},
            {"computeTimeUs", computeTimeUs}};
}

// success, err
static std::tuple<bool, std::string> parseState(const std::string inputStateStr, std::array<Face, 54> &state)
{
    if (inputStateStr.size() != 54)
        return {false, "State must be exactly 54 characters"};

    std::unordered_map<char, Face> colorToFace;

    const Face faceOrder[] = {Face::UP, Face::FRONT, Face::RIGHT, Face::BACK, Face::LEFT, Face::DOWN};
    const char *faces[] = {"UP", "FRONT", "RIGHT", "BACK", "LEFT", "DOWN"};

    for (int i = 0; i < 6; ++i)
    {
        char centreColor = inputStateStr[Constants::CENTRE_INDICES[i]];

        if (colorToFace.count(centreColor))
            return {false, std::string("Color '") + centreColor + "' is the centre of multiple faces"};

        colorToFace[centreColor] = faceOrder[i];
    }

    std::array<int, 6> counts = {};
    for (size_t i = 0; i < 54; ++i)
    {
        auto it = colorToFace.find(inputStateStr[i]);
        if (it == colorToFace.end())
            return {false, fmt::format("Unknown color '{}' at position {} (not a middle piece color)", inputStateStr[i], i)};

        state[i] = it->second;
        counts[static_cast<int>(it->second)]++;
    }

    // sanity check
    if (state.size() != 54)
        return {false, "Parsed state is not 54 length"};

    for (int i = 0; i < 6; ++i)
    {
        if (counts[i] != 9)
        {
            return {false, fmt::format("Face '{}' appears {} times, expected 9", faces[i], counts[i])};
        }
    }

    return {true, std::string()};
}

int main()
{
    httplib::Server svr;

    svr.set_default_headers({{"Access-Control-Allow-Origin", "*"},
                             {"Access-Control-Allow-Methods", "POST, GET, OPTIONS"},
                             {"Access-Control-Allow-Headers", "Content-Type"}});

    svr.Get("/health", [](const httplib::Request &, httplib::Response &res)
            { res.set_content("ok", "text/plain"); });

    svr.Post(
        "/solve",
        [](const httplib::Request &req, httplib::Response &res)
        {
            if (req.method != "POST")
            {
                res.status = 405;
                res.set_content(errorResponse("Only POST method is allowed", "METHOD_NOT_ALLOWED").dump(), "application/json");
                return;
            }

            json body;
            try
            {
                body = json::parse(req.body);
            }
            catch (const json::exception &)
            {
                res.status = 400;
                res.set_content(errorResponse("Invalid JSON body", "BAD_REQUEST").dump(), "application/json");

                fmt::print(stderr, "Failed to parse JSON body: {}\n", req.body);
                return;
            }

            if (!body.contains("state") || !body["state"].is_string())
            {
                res.status = 400;
                res.set_content(errorResponse("Missing or invalid 'state' field", "BAD_REQUEST").dump(), "application/json");
                fmt::print(stderr, "Missing or invalid 'state' field in request body: {}\n", req.body);
                return;
            }

            std::string stateStr = body["state"];

            std::array<Face, 54> state;

            auto [success, error] = parseState(stateStr, state);

            if (!success)
            {
                res.status = 422;
                res.set_content(errorResponse(error, "INVALID_STATE").dump(), "application/json");
                fmt::print(stderr, "Invalid state: {}\n", error);
                return;
            }

            auto start = std::chrono::steady_clock::now();

            SolveResult result = solveCube(state);

            auto elapsedns = std::chrono::duration_cast<std::chrono::microseconds>(
                                 std::chrono::steady_clock::now() - start)
                                 .count();

            if (!result.success)
            {
                res.status = 422;
                res.set_content(errorResponse(result.error, "ILLEGAL_CUBE").dump(), "application/json");
                fmt::print(stderr, "Illegal cube: {}\n", result.error);
                return;
            }

            json resp = okResponse(result.moves, result.moves.size(), elapsedns);

            res.set_content(resp.dump(), "application/json");
        }

    );

    fmt::print("Cube solver server listening on http://0.0.0.0:8080\n");

    svr.listen("0.0.0.0", 8080);

    return 0;
}
