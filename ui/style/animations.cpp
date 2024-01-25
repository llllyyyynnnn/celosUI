#include "../ui.h"

namespace celosia::animations::functions {
    float calc_linear(float current_value, const float goal_value, float speed) {
        ImGuiIO* io = celosia::render::io;
        speed += animations::base_speed;

        if (speed < 0)
            speed = 0;

        if (current_value == goal_value) return goal_value;

        if (current_value > goal_value) {
            current_value -= speed * io->DeltaTime;
            if (current_value <= goal_value)
                return goal_value;
        }
        else if (current_value < goal_value)
        {
            current_value += speed * io->DeltaTime;
            if (current_value >= goal_value)
                return goal_value;
        }

        return current_value;
    }

    float calc_smooth(float current_value, const float goal_value, float speed) {
        ImGuiIO* io = celosia::render::io;
        speed += base_speed;

        if (speed < 0)
            speed = 0;

        if ((current_value == goal_value) ||
            (current_value + 0.11f >= goal_value && current_value < goal_value) ||
            (current_value - 0.11f <= goal_value && current_value > goal_value)) // this works with any values pretty sure
            return goal_value;

        current_value += (goal_value - current_value) * io->DeltaTime * speed;
        return current_value;
    }

    float linear(const std::string& value, const float goal_value, float speed) {
        float res = calc_linear(str_map[value], goal_value, speed);
        str_map[value] = res;
        return res;
    }

    float smooth(const std::string& value, const float goal_value, float speed) {
        float res = calc_smooth(str_map[value], goal_value, speed);
        str_map[value] = res;
        return res;
    }

    float linear(const int& value, const float goal_value, float speed) {
        float res = calc_linear(int_map[value], goal_value, speed);
        int_map[value] = res;
        return res;
    }

    float smooth(const int& value, const float goal_value, float speed) {
        float res = calc_smooth(int_map[value], goal_value, speed);
        int_map[value] = res;
        return res;
    }
}

namespace celosia::animations {
    float set(const std::string& value, const float goal_value, float speed, e_method method) {
        if (method == e_method::smooth)
            return functions::smooth(value, goal_value, speed);

        if (method == e_method::linear)
            return functions::linear(value, goal_value, speed);
    }

    ImVec2 set(const std::string& value, const ImVec2 goal_value, float speed, e_method method) {
        if (method == e_method::smooth)
            return ImVec2(functions::smooth(value + ", x", goal_value.x, speed), functions::smooth(value + ", y", goal_value.y, speed));

        if (method == e_method::linear)
            return ImVec2(functions::linear(value + ", x", goal_value.x, speed), functions::linear(value + ", y", goal_value.y, speed));
    }

    ImVec4 set(const std::string& value, const ImVec4 goal_value, float speed, e_method method) {
        if (method == e_method::smooth)
            return ImVec4(functions::smooth(value + ", x", goal_value.x, speed), functions::smooth(value + ", y", goal_value.y, speed), functions::smooth(value + ", z", goal_value.z, speed), functions::smooth(value + ", w", goal_value.w, speed));

        if (method == e_method::linear)
            return ImVec4(functions::linear(value + ", x", goal_value.x, speed), functions::linear(value + ", y", goal_value.y, speed), functions::linear(value + ", z", goal_value.z, speed), functions::linear(value + ", w", goal_value.w, speed));
    }

/*
    ImColor set(const std::string& value, const ImColor goal_value, float speed, e_method method) {
        if (method == e_method::smooth)
            return ImColor(functions::smooth(value + ", x", goal_value.Value.x, speed), functions::smooth(value + ", y", goal_value.Value.y, speed), functions::smooth(value + ", z", goal_value.Value.z, speed), functions::smooth(value + ", w", goal_value.Value.w, speed));

        if (method == e_method::linear)
            return ImColor(functions::linear(value + ", x", goal_value.Value.x, speed), functions::linear(value + ", y", goal_value.Value.y, speed), functions::linear(value + ", z", goal_value.Value.z, speed), functions::linear(value + ", w", goal_value.Value.w, speed));
    }
*/

    float set(const int& value, const float goal_value, float speed, e_method method) {
        if (method == e_method::smooth)
            return functions::smooth(value, goal_value, speed);

        if (method == e_method::linear)
            return functions::linear(value, goal_value, speed);
    }

    ImVec2 set(const int& value, const ImVec2 goal_value, float speed, e_method method) {
        return set(std::to_string(value), goal_value, speed, method);
    }

    ImVec4 set(const int& value, const ImVec4 goal_value, float speed, e_method method) {
        return set(std::to_string(value), goal_value, speed, method);
    }
}