#pragma once

class Doors {
enum DoorsState {
    OPENING,
    OPENED,
    CLOSING,
    CLOSED
};
public:
    void open();
    void close();

private:
    DoorsState _state = OPENED;

};