/*
 *                                   1byt3
 *
 *                              License Notice
 *
 * 1byt3 provides a commercial license agreement for this software. This
 * commercial license can be used for development of proprietary/commercial
 * software. Under this commercial license you do not need to comply with the
 * terms of the GNU Affero General Public License, either version 3 of the
 * License, or (at your option) any later version.
 *
 * If you don't receive a commercial license from us (1byt3), you MUST assume
 * that this software is distributed under the GNU Affero General Public
 * License, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Contact us for additional information: customers at 1byt3.com
 *
 *                          End of License Notice
 */

/*
 * MQTT 5 Low Level Packet Library
 *
 * Copyright (C) 2017 1byt3, customers at 1byt3.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PKT_SUBACKMSG_HPP__
#define __PKT_SUBACKMSG_HPP__

#include "Properties.hpp"
#include "Packet.hpp"
#include "Common.hpp"

#include <list>

namespace m5 {

class PktSubAckMsg : public Packet
{
private:
	std::list<uint8_t> _reasonCodes;

	enum StatusCode writeVariableHeader(AppBuf &buf) override;
	enum StatusCode writePayload(AppBuf &buf) override;

	enum StatusCode readVariableHeader(AppBuf &buf) override;
	enum StatusCode readPayload(AppBuf &buf) override;

protected:
	PktSubAckMsg(enum PktType type);
	PktSubAckMsg(enum PktType type, AppBuf &buf);

public:
	virtual ~PktSubAckMsg() {}

	enum StatusCode packetId(uint16_t id) { return Packet::packetId(id); }
	uint16_t packetId(void) { return Packet::packetId(); }

	void append(enum ReasonCode rc) { this->_reasonCodes.push_back((uint8_t)rc); }
	const std::list<uint8_t> &reasonCodes() const { return _reasonCodes; }

	enum StatusCode reasonString(const uint8_t *data, uint16_t size);
	enum StatusCode reasonString(const char *str);
	const ByteArray &reasonString(void) const;

	enum StatusCode userProperty(const uint8_t *key, uint16_t keySize,
				     const uint8_t *value, uint16_t valueSize);
	enum StatusCode userProperty(const char *key, const char *val);
	const UserProperty &userProperty(void) const;

	uint32_t writeTo(AppBuf &buf) override;
	uint32_t readFrom(AppBuf &buf) override;
};

}

#endif

