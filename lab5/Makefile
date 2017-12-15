CC:=avrasm2

TARGET:=app/main.asm

MMCU:=atmega2560

MMCU_SHORT:=m2560

COM_PORT:=/dev/tty.usbmodem1411

make: $(TARGET)
	wine avrasm2 -f I -o program.hex app/main.asm
	@#-p will ignore error if folder already exists
	@mkdir -p out
	@mv *.hex out

	@echo 'Successfully built project'

clean:
	@echo 'Removing out folder'
	@rm -rf out/

.PHONY: clean

send:
	avrdude -p $(MMCU_SHORT) -c stk500v2 -P $(COM_PORT) -b 115200 -F -U flash:w:out/program.hex

.PHONY: send