# Dactyl Manuform - Custom 4x6 with Vial

This acts as a reference of what i have done in case i need to repeat it again.

## Handwritten:

Ok so Serial comms worked fuck-all, but inside arduino-sanity is a i2c-test which worked out.
Now i only have to get it working on a keyboard. Currently trying to remember what to flash so that it looks keyboardy to begin with.
- tried qmk fork, forgot run command.
- remembered i was polishing the vial ui layout
- opened `QMK MSYS` at vial-qmk
- flashed `qmk flash -kb handwired/dactyl_slx -km vial -bl avrdude-split-left` (and without -bl) that's not it..
- using eeprom handedness sounds good, `#define EE_HANDS` in config.h and then `-bl avrdude-split-left` or `-bl avrdude-split-right`

# AI Generated

## Setup

- install QMK MSYS
- clone vial fork of qmk and run MSYS there
- run `make git-submodule`
- run `qmk doctor`
- run `create_symlink.ps1`

## Flashing

- run `qmk flash -kb handwired/dactyl_slx -km vial`

## 🔧 Hardware Configuration

### Default Pin Configuration (LEFT HALF)
**Update these in `config.h` to match your actual wiring!**

- **Rows**: D4, C6, D7, E6, B4
- **Columns**: F6, F7, B1, B3, B2, B6
- **Serial Communication**: D0
- **Handedness Detection**: F4

### Matrix Configuration
- 5 rows × 6 columns per half
- Total: 10 rows × 6 columns
- COL2ROW diode direction

## ⚙️ Building the Firmware

### Prerequisites
1. Install QMK MSYS or QMK CLI
2. Clone QMK firmware repository
3. Install Vial QMK fork (recommended) or add Vial to standard QMK

### Option 1: Using Vial QMK Fork (Recommended)
```powershell
# Clone Vial QMK
git clone https://github.com/vial-kb/vial-qmk.git
cd vial-qmk

# IMPORTANT: Initialize submodules (LUFA, ChibiOS, etc.)
git submodule update --init --recursive

# Copy this project into keyboards directory
# Copy the entire 'vial' folder to: keyboards/handwired/dactyl_manuform_custom/
# Or create a symbolic link

# Build the firmware
qmk compile -kb handwired/dactyl_manuform_custom -km vial
```

### Option 2: Building Locally
If you're working directly in this folder and have QMK configured:
```powershell
# Make sure you're in a QMK environment (QMK MSYS or have QMK CLI installed)
# Navigate to your QMK root directory and run:
qmk compile -kb <path_to_this_folder> -km vial
```

## 🔌 Flashing the Firmware

### For Pro Micro or Compatible Controllers
```powershell
# Put keyboard into bootloader mode (short RST to GND twice)
qmk flash -kb handwired/dactyl_manuform_custom -km vial
```

### Manual Flashing
If automatic flashing doesn't work:
```powershell
# Build creates a .hex file
# Use QMK Toolbox or avrdude to flash manually
avrdude -p atmega32u4 -c avr109 -P COM<X> -U flash:w:dactyl_manuform_custom_vial.hex
```

## 🧪 Testing Your First Half

### Before Building
1. **Verify your wiring matches the pin configuration** in `config.h`
2. Update `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` if needed
3. Confirm you're using the correct microcontroller (`atmega32u4` for Pro Micro)
4. Set `MASTER_LEFT` or `MASTER_RIGHT` in `config.h` based on which half you're testing

### Testing Process
1. Flash the firmware to your soldered half
2. Open Vial software (download from vial.rocks)
3. Connect your keyboard
4. Use Vial's matrix tester to verify each key works
5. Fix any issues before soldering the second half

### Common Issues
- **Keys not registering**: Check solder joints and diode orientation
- **Wrong keys triggering**: Verify row/column pin assignments
- **Keyboard not detected**: Check USB connection and bootloader

## 🎹 Using Vial

1. Download Vial from https://get.vial.today/
2. Connect your keyboard
3. Vial will automatically detect it
4. Configure your keymap visually
5. Changes are saved directly to the keyboard

### Vial Unlock Combo
To prevent accidental keymap changes, the keyboard is locked by default.
- **Unlock keys**: Top-left (0,0) and middle-right (2,5)
- Press both simultaneously to unlock for configuration

## 🛠️ Customization

### Changing the Layout
Edit `keymaps/vial/keymap.c` to modify the default keymap.

### Adjusting Matrix Size
If your Dactyl Manuform has a different size:
1. Update `MATRIX_ROWS` and `MATRIX_COLS` in `config.h`
2. Update the layout in `info.json`
3. Update `vial.json` to match
4. Adjust `keymap.c` accordingly

### Adding Features
Enable features in `rules.mk`:
- `RGBLIGHT_ENABLE = yes` - RGB underglow
- `OLED_ENABLE = yes` - OLED display support
- `ENCODER_ENABLE = yes` - Rotary encoder support

## 📝 Important Notes

- **Master/Slave Configuration**: Currently set to `MASTER_LEFT`. The left half will be the master that connects to your computer.
- **VIAL_KEYBOARD_UID**: The unique ID in `config.h` should be changed to a unique 8-byte value for your keyboard.
- **Debounce**: Set to 5ms, increase if you experience key chatter.

## 🔗 Resources

- [Vial Documentation](https://get.vial.today/docs/)
- [QMK Documentation](https://docs.qmk.fm/)
- [Dactyl Manuform Build Guide](https://github.com/abstracthat/dactyl-manuform)

## 📄 License

This firmware is based on QMK and is licensed under GPL-2.0-or-later.
