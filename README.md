# BLEMonitor

```
Connecting a4:c1:38:cf:fa:96
lld_pdu_get_tx_flush_nb HCI packet count mismatch (0, 1)
CORRUPT HEAP: Bad head at 0x3ffba854. Expected 0xabba1234 got 0x3ffba908
abort() was called at PC 0x4008bf75 on core 1

ELF file SHA256: 0000000000000000

Backtrace: 0x4008ed14:0x3ffc6cb0 0x4008ef91:0x3ffc6cd0 0x4008bf75:0x3ffc6cf0 0x4008c0a1:0x3ffc6d20 0x4014ab47:0x3ffc6d40 0x40144819:0x3ffc7000 0x401447a1:0x3ffc7050 0x400934a1:0x3ffc7080 0x4008c716:0x3ffc70a0 0x4008be6d:0x3ffc70c0 0x4000bec7:0x3ffc70e0 0x40179df5:0x3ffc7100 0x400d36e7:0x3ffc7120 0x400d45d0:0x3ffc7140 0x400d3ac2:0x3ffc7170 0x400d1bb5:0x3ffc71d0 0x400d25e4:0x3ffc7210 0x400d267b:0x3ffc7230 0x400d8640:0x3ffc7250 0x4008fff6:0x3ffc7270

Rebooting...
ets Jun  8 2016 00:22:57

rst:0xc (SW_CPU_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0018,len:4

Decoding stack results
0x4008ed14: invoke_abort at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/esp32/panic.c line 156
0x4008ef91: abort at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/esp32/panic.c line 171
0x4008bf75: lock_acquire_generic at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/newlib/locks.c line 143
0x4008c0a1: _lock_acquire_recursive at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/newlib/locks.c line 171
0x4014ab47: _vfiprintf_r at ../../../.././newlib/libc/stdio/vfprintf.c line 860
0x40144819: fiprintf at ../../../.././newlib/libc/stdio/fiprintf.c line 50
0x401447a1: __assert_func at ../../../.././newlib/libc/stdlib/assert.c line 59
0x400934a1: multi_heap_free at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/heap/multi_heap_poisoning.c line 218
0x4008c716: heap_caps_free at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/heap/heap_caps.c line 268
0x4008be6d: _free_r at /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/newlib/syscalls.c line 42
0x40179df5: operator delete(void*) at /builds/idf/crosstool-NG/.build/src/gcc-5.2.0/libstdc++-v3/libsupc++/del_op.cc line 46
0x400d36e7: std::_Rb_tree  , std::_Select1st   >, std::less , std::allocator   > >::_M_erase(std::_Rb_tree_node   >*) at d:\arduino\arduino-1.8.13\portable\packages\esp32\tools\xtensa-esp32-elf-gcc\1.22.0-97-gc752ad5-5.2.0\xtensa-esp32-elf\include\c++\5.2.0\ext/new_allocator.h line 110
0x400d45d0: BLEDevice::removePeerDevice(unsigned short, bool) at d:\arduino\arduino-1.8.13\portable\packages\esp32\tools\xtensa-esp32-elf-gcc\1.22.0-97-gc752ad5-5.2.0\xtensa-esp32-elf\include\c++\5.2.0\bits/stl_tree.h line 1075
0x400d3ac2: BLEClient::connect(BLEAddress, esp_ble_addr_type_t) at D:\Arduino\arduino-1.8.13\portable\packages\esp32\hardware\esp32\1.0.5\libraries\BLE\src\BLEClient.cpp line 144
0x400d1bb5: ConnectBLEClients() at xxx/registerLY.ino line 97
0x400d25e4: loopAll() at xxx/x00.ino line 55
0x400d267b: loop() at xxx/LYWSD03MMClogger.ino line 67
```

