#include "mbed.h"
#include <chrono>

#define MAXIMUM_BUFFER_SIZE 32

using namespace std::chrono_literals;
static AnalogIn ain(PA_5);
static BufferedSerial serial_port(PA_9, PA_10);
static BufferedSerial esp_serial(PA_2, PA_3);
static DigitalIn button(PA_3);
static PwmOut led(PB_5);

FileHandle *mbed::mbed_override_console(int fd) { return &serial_port;}

int main() {
    serial_port.set_baud(9600);
	serial_port.set_format(8, BufferedSerial::None, 1);

	esp_serial.set_baud(9600);
	esp_serial.set_format(8, BufferedSerial::None, 1);

    button.mode(PullUp);
    unsigned char p = ain.read_u16()>>8;
    unsigned char buf[] = { p };
    while(1) {
        p = ain.read_u16();
        unsigned char buf[0] = p;
        esp_serial.write(buf, sizeof(buf));
        ThisThread::sleep_for(1000);
    }
}
