#ifndef WARSPIDER_SUBSYSTEM_H
#define WARSPIDER_SUBSYSTEM_H

namespace WarSpider {

enum class SubsystemStatus {
    NOT_STARTED,
    READY,
    FAILED
};

class Subsystem {
public:
    virtual ~Subsystem() = default;

    virtual bool begin() = 0;

    SubsystemStatus getStatus() const;

protected:
    SubsystemStatus status = SubsystemStatus::NOT_STARTED;
};

}

#endif