/*
* Wire
* Copyright (C) 2019 Wire Swiss GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef FRAME_DECRYPTOR_H_
#define FRAME_DECRYPTOR_H_

#include "api/crypto/framedecryptorinterface.h"
#include "rtc_base/refcountedobject.h"
#include <openssl/evp.h>
#include <openssl/cipher.h>

namespace wire {

class FrameDecryptor : public rtc::RefCountedObject<webrtc::FrameDecryptorInterface>
{
public:
	FrameDecryptor();
	~FrameDecryptor();

	void SetKey(const uint8_t *key);

	int Decrypt(cricket::MediaType media_type,
		    const std::vector<uint32_t>& csrcs,
		    rtc::ArrayView<const uint8_t> additional_data,
		    rtc::ArrayView<const uint8_t> encrypted_frame,
		    rtc::ArrayView<uint8_t> frame,
		    size_t* bytes_written);

	size_t GetMaxPlaintextByteSize(cricket::MediaType media_type,
				       size_t encrypted_frame_size);

private:
	EVP_CIPHER_CTX *_ctx;
	bool _ready;
};

}  // namespace wire

#endif  // FRAME_DECRYPTOR_H_
