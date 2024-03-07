#pragma once

#include <algorithm>
#include <concepts>

namespace util_ai {
template <typename T, typename WorldState>
concept action = requires(T t, WorldState ws) {
  { t.utility(ws) } -> std::convertible_to<double>;
  { t.execute(ws) };
};

template <typename WorldState> class base_action {
public:
  virtual double utility(const WorldState &ws) = 0;

  virtual void execute(WorldState &ws) = 0;

  virtual ~base_action() = default;
};

template <typename WorldState, action<WorldState> Action =
                                   base_action<WorldState>>
class agent {
public:
  constexpr agent() = default;

  void add_action(std::unique_ptr<Action> a) {
    _actions.push_back(std::move(a));
  }

  void decide_and_act(WorldState &ws) {
    auto max_it = std::max_element(
        _actions.begin(), _actions.end(),
        [&ws](const auto &a, const auto &b) {
          return a->utility(ws) < b->utility(ws);
        });

    if (max_it != _actions.end()) {
      (*max_it)->execute(ws);
    }
  }

private:
  std::vector<std::unique_ptr<Action>> _actions;
};
} // namespace util_ai