
#include "Communicator.h"
#include "defines.h"
#include "enums.h"
#include "storage.h"


Communicator::Communicator(Packet* rx, Packet* tx)
{
    this->rx = rx;
    this->tx = tx;
}

void Communicator::begin()
{
    uart.begin(UART_BAUD_RATE);
    while (!uart)
    {
        ; // Wait for serial port to connect. Needed for native USB
    }

    uart.println("Remove me, I am alive");

    bluetooth.begin(BLUETOOTH_BAUD_RATE);
}

void Communicator::processCommands()
{
    read(uart);
    write(uart);
}

void Communicator::read(HardwareSerial &interface)
{
    static bool has_stx = false;
    static bool has_etx = false;
    static bool has_dle = false;
    static uint16_t index = 0;
    uint8_t byte = 0;

    if (nullptr == rx)
    {
        return;
    }

    while (interface.available())
    {
        byte = interface.read();

        // Search for packet start
        if (!has_stx)
        {
            has_stx = FrameByte::STX == byte && !has_dle;
            if (has_stx)
            {
                index = 0;
                rx->reset();
                                
                continue;
            }
        }

        // Search for packet end
        if (!has_etx)
        {
            has_etx = FrameByte::ETX == byte && has_stx && !has_dle;
            if (has_etx)
            {
                // Reset packet parsing flags
                has_stx = false;
                has_etx = false;
                has_dle = false;

                return;
            }
        }

        // Packet escape flag
        has_dle = FrameByte::DLE == byte && !has_dle;
        if (has_dle)
        {
            continue;
        }

        // Packet payload
        // <OPERATION> <COMMAND> <HARDWARE_INDEX> <DATA>
        if (has_stx)
        {
            switch (index)
            {
            case 0:
                rx->setOperation(byte);
                break;
            case 1:
                rx->setCommand(byte);
                 break;
            case 2:
                rx->setHardwareIndex(byte);
                 break;
            default:
                rx->appendData(&byte, 1);
                break;
            }

            index++;
        }
    }
}

void Communicator::write(HardwareSerial &interface)
{
    if (nullptr == tx || !tx->pending())
    {
        return;
    }

    uint8_t *p_data = tx->getDataPointer();
    uint16_t data_size = tx->getDataBytesCount();
    if (p_data != nullptr)
    {
        interface.write(FrameByte::STX);
        interface.write(tx->operation());
        interface.write(tx->command());
        interface.write(tx->hardwareIndex());

        for (uint16_t i = 0; i < data_size; ++i)
        {
            if (isEscapable(p_data[i]))
            {
                interface.write(FrameByte::DLE);
            }
            interface.write(p_data[i]);
        }
        interface.write(FrameByte::ETX);
    }

    tx->reset();
}

bool Communicator::isEscapable(uint8_t byte)
{
    return (byte == FrameByte::STX || byte == FrameByte::ETX || byte == FrameByte::DLE);
}


 

    // char buf[80];
    // byte tmp_wheel;
    // byte tmp_mode;

    // if (cmdPending == false)
    // {
    //   currentCommand = Serial.read();
    // }

    // //cmdPending = true;

    // switch (currentCommand)
    // {
    // case 'a':
    //   break;

    // // Set the fixed RPM value
    // case 'f':
    //   mode = FIXED_RPM;
    //   // Wait for the new RPM bytes
    //   while (Serial.available() < 2)
    //   {
    //   }

    //   wanted_rpm = word(Serial.read(), Serial.read());

    //   setRPM(wanted_rpm);
    //   break;

    // // Save the current config
    // case 'c':
    //   saveConfig();
    //   break;

    // // Send the list of wheel names
    // case 'L':
    //   for (byte x = 0; x < MAX_WHEELS; x++)
    //   {
    //     strcpy_P(buf, Wheels[x].decoder_name);
    //     Serial.println(buf);
    //     //Serial.println((const __FlashStringHelper*)triggerPattern.Wheels[x].decoder_name);
    //   }
    //   break;

    // // Send the number of wheels
    // case 'n':
    //   Serial.println(MAX_WHEELS);
    //   break;

    // // Send the number (index) of the current wheel
    // case 'N':
    //   Serial.println(selected_wheel);
    //   break;

    // // Send the size of the current wheel
    // case 'p':
    //   Serial.println(Wheels[selected_wheel].wheel_max_edges);
    //   break;

    // // Send the pattern for the current wheel
    // case 'P':
    //   numTeeth = pgm_read_word(Wheels[selected_wheel].wheel_max_edges);

    //   for (uint16_t x = 0; x < Wheels[selected_wheel].wheel_max_edges; ++x)
    //   {
    //     if (x != 0)
    //     {
    //       Serial.print(",");
    //     }

    //     byte tempByte = pgm_read_byte(&Wheels[selected_wheel].edge_states_ptr[x]);
    //     Serial.print(tempByte);
    //   }
    //   Serial.println("");
    //   // 2nd row of data sent is the number of degrees the wheel runs over (360 or 720 typically)
    //   Serial.println(Wheels[selected_wheel].wheel_degrees);
    //   break;

    // // Send the current RPM
    // case 'R':
    //   Serial.println(wanted_rpm);
    //   break;

    // // Set the current wheel
    // case 'S':
    //   while (Serial.available() < 1)
    //   {
    //   }
    //   tmp_wheel = Serial.read();
    //   if (tmp_wheel < MAX_WHEELS)
    //   {
    //     selected_wheel = tmp_wheel;
    //     display_new_wheel();
    //   }
    //   break;

    // // Just a test method for switching the to the next wheel
    // case 'X':
    //   select_next_wheel_cb();

    //   strcpy_P(buf, Wheels[selected_wheel].decoder_name);
    //   Serial.println(buf);
    //   break;

    // default:
    //   break;
    // }

    // cmdPending = false;


// void display_new_wheel()
// {
//   reset_new_OCR1A(wanted_rpm);

//   // Reset to beginning of the wheel pattern
//   edge_counter = 0;

//   // if (mode != LINEAR_SWEPT_RPM)
//   //   reset_new_OCR1A(wanted_rpm);
//   // else
//   //   compute_sweep_stages(&sweep_low_rpm, &sweep_high_rpm);
//   // edge_counter = 0; // Reset to beginning of the wheel pattern */
// }

// // Selects the next wheel, if at the end, wrap to the beginning of the list,
// // re-calculate the OCR1A value (RPM) and reset, return user information on the
// // selected wheel and current RPM
// void select_next_wheel_cb()
// {
//   if (selected_wheel == (MAX_WHEELS - 1))
//     selected_wheel = 0;
//   else
//     selected_wheel++;

//   display_new_wheel();
// }

// // Changes the RPM based on user input
// //
// // Prompts user for new RPM, reads it, validates it's within range, sets lock to
// // prevent a race condition with the sweeper, free's memory of SweepSteps
// // structure IF allocated, sets the mode to fixed RPM, recalculates the new OCR1A
// // value based on the user specificaed RPM and sets it and then removes the lock
// void setRPM(uint32_t newRPM)
// {
//   if (newRPM < 10)
//   {
//     return;
//   }

//   reset_new_OCR1A(newRPM);

//   wanted_rpm = newRPM;
// }

// // Figures out the amount of free RAM remaining and returns it to the caller
// // \return amount of free memory
// uint16_t freeRam()
// {
//   extern int __heap_start, *__brkval;
//   int v;
//   return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
// }