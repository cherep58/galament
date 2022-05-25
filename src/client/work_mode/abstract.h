#ifndef GALAMENT_CLIENT_WORK_MODE_ABSTRACT_H
#define GALAMENT_CLIENT_WORK_MODE_ABSTRACT_H

#include <string>
#include <string_view>

namespace galament::client::work_mode {

class Abstract {
public:
    Abstract(std::string_view address);
    virtual ~Abstract() = default;

    virtual void Run() = 0;

protected:
    std::string address_;
};

} // namespace galament::client::work_mode

#endif