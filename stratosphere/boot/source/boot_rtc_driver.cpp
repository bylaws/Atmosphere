/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <switch.h>
#include <stratosphere.hpp>
#include "boot_functions.hpp"
#include "boot_rtc_driver.hpp"

Result RtcDriver::ReadRtcRegister(u8 *out, u8 address) {
    const u8 update_addr = 0x04;
    const u8 update_val = 0x10;
    Result rc = Boot::WriteI2cRegister(this->i2c_session, &update_val, sizeof(update_val), &update_addr, sizeof(update_addr));
    if (R_FAILED(rc)) {
        return rc;
    }
    svcSleepThread(16'000'000ul);
    return Boot::ReadI2cRegister(this->i2c_session, out, sizeof(*out), &address, sizeof(address));
}

Result RtcDriver::GetRtcIntr(u8 *out) {
    const u8 addr = 0x00;
    return Boot::ReadI2cRegister(this->i2c_session, out, sizeof(*out), &addr, sizeof(addr));
}

Result RtcDriver::GetRtcIntrM(u8 *out) {
    const u8 addr = 0x01;
    return this->ReadRtcRegister(out, addr);
}
