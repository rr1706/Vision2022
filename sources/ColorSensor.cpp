/* #include <linux/i2c-dev.h>
#include <sys/ioctl.h>

int file;
int adapter_nr = 2;
char filename[20];

snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

if ((file = open(filename, O_RDWR);) < 0) {
  exit(1);
}

int addr = 0x40;
if (ioctl(file, I2C_SLAVE, addr) < 0) {
  exit(1);
}

__u8 reg = 0x10;
__s32 res;
char buf[10];
if ((res = i2c_smbus_read_word_data(file, reg)) < 0) {
  // ERROR HANDLING: i2c transaction failed
} else {
  // res contains the read word
}

buf[0] = reg;
buf[1] = 0x43;
buf[2] = 0x65;
if (write(file, buf, 3) != 3) {
  // ERROR HANDLING: i2c transaction failed
}
 */