#include "crypto.h"

/*static const DWORD AesKeyV4[] = {
	0x07833D05, 0x88F0E5F9, 0x68A65EEB, 0xC737F06C, 0x94BE085D, 0x383E06CD,
	0x1B75E241, 0x21F3EB7A, 0x4914C3A5, 0x9FC62C41, 0xEDAE3CA8, 0x0B2B518A,
	0x74F07B8D, 0x3947BCEE, 0x71852CD0, 0x1821BA25, 0xBA683A7B, 0x3F605838,
	0xF37CF9DE, 0xA0A67479, 0x7A94B8C2, 0x10CC5B10, 0x0E11944F, 0x08EDE7FE,
	0xD171A08F, 0x749DEC9B, 0xC956998B, 0x4BFDB4A3, 0xA8E240CE, 0x65419151,
	0xFAFBCC8A, 0x819F8EF5, 0xA1DFF829, 0x9BF5987C, 0x70AE58A6, 0x0725312B,
	0xEB00C731, 0x1F1262F4, 0x43FB0BFF, 0x9E8DF3A5, 0x0779DDC5, 0xEA7EA064,
	0xA6A625EC, 0x718B3818, 0xD1F1684A, 0x3B577D21, 0x9D08ED45, 0xD68F4DA9
};*/

static const BYTE AesKeyV4[] = {
	0x05, 0x3D, 0x83, 0x07, 0xF9, 0xE5, 0xF0, 0x88, 0xEB, 0x5E, 0xA6, 0x68, 0x6C, 0xF0, 0x37, 0xC7,
	0x5D, 0x08, 0xBE, 0x94, 0xCD, 0x06, 0x3E, 0x38, 0x41, 0xE2, 0x75, 0x1B, 0x7A, 0xEB, 0xF3, 0x21,
	0xA5, 0xC3, 0x14, 0x49, 0x41, 0x2C, 0xC6, 0x9F, 0xA8, 0x3C, 0xAE, 0xED, 0x8A, 0x51, 0x2B, 0x0B,
	0x8D, 0x7B, 0xF0, 0x74, 0xEE, 0xBC, 0x47, 0x39, 0xD0, 0x2C, 0x85, 0x71, 0x25, 0xBA, 0x21, 0x18,
	0x7B, 0x3A, 0x68, 0xBA, 0x38, 0x58, 0x60, 0x3F, 0xDE, 0xF9, 0x7C, 0xF3, 0x79, 0x74, 0xA6, 0xA0,
	0xC2, 0xB8, 0x94, 0x7A, 0x10, 0x5B, 0xCC, 0x10, 0x4F, 0x94, 0x11, 0x0E, 0xFE, 0xE7, 0xED, 0x08,
	0x8F, 0xA0, 0x71, 0xD1, 0x9B, 0xEC, 0x9D, 0x74, 0x8B, 0x99, 0x56, 0xC9, 0xA3, 0xB4, 0xFD, 0x4B,
	0xCE, 0x40, 0xE2, 0xA8, 0x51, 0x91, 0x41, 0x65, 0x8A, 0xCC, 0xFB, 0xFA, 0xF5, 0x8E, 0x9F, 0x81,
	0x29, 0xF8, 0xDF, 0xA1, 0x7C, 0x98, 0xF5, 0x9B, 0xA6, 0x58, 0xAE, 0x70, 0x2B, 0x31, 0x25, 0x07,
	0x31, 0xC7, 0x00, 0xEB, 0xF4, 0x62, 0x12, 0x1F, 0xFF, 0x0B, 0xFB, 0x43, 0xA5, 0xF3, 0x8D, 0x9E,
	0xC5, 0xDD, 0x79, 0x07, 0x64, 0xA0, 0x7E, 0xEA, 0xEC, 0x25, 0xA6, 0xA6, 0x18, 0x38, 0x8B, 0x71,
	0x4A, 0x68, 0xF1, 0xD1, 0x21, 0x7D, 0x57, 0x3B, 0x45, 0xED, 0x08, 0x9D, 0xA9, 0x4D, 0x8F, 0xD6
};

const BYTE AesKeyV5[] = {
	0xCD, 0x7E, 0x79, 0x6F, 0x2A, 0xB2, 0x5D, 0xCB, 0x55, 0xFF, 0xC8, 0xEF, 0x83, 0x64, 0xC4, 0x70 };

const BYTE AesKeyV6[] = {
	0xA9, 0x4A, 0x41, 0x95, 0xE2, 0x01, 0x43, 0x2D, 0x9B, 0xCB, 0x46, 0x04, 0x05, 0xD8, 0x4A, 0x21 };

static const BYTE SBox[] = {
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B,
	0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
	0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26,
	0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2,
	0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
	0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED,
	0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F,
	0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
	0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC,
	0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14,
	0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
	0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D,
	0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F,
	0x4B, 0xBD, 0x8B, 0x8A, 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
	0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11,
	0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F,
	0xB0, 0x54, 0xBB, 0x16
};

static const BYTE SBoxR[] = {
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E,
	0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
	0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32,
	0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49,
	0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50,
	0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05,
	0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
	0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41,
	0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8,
	0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
	0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B,
	0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59,
	0x27, 0x80, 0xEC, 0x5F, 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
	0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D,
	0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63,
	0x55, 0x21, 0x0C, 0x7D
};


static void ShiftRows(BYTE *block)
{
	BYTE temp;

	//block[ 0  ] = block[ 0  ];
	//block[ 4  ] = block[ 4  ];
	//block[ 8  ] = block[ 8  ];
	//block[ 12 ] = block[ 12 ];

	temp        = block[ 13 ];
	block[ 13 ] = block[ 1  ];
	block[ 1  ] = block[ 5  ];
	block[ 5  ] = block[ 9  ];
	block[ 9  ] = temp;

	temp        = block[ 10 ];
	block[ 10 ] = block[ 2  ];
	block[ 2  ] = temp;

	temp        = block[ 7  ];
	block[ 7  ] = block[ 3  ];
	block[ 3  ] = block[ 15 ];
	block[ 15 ] = block[ 11 ];
	block[ 11 ] = temp;

	temp        = block[ 6  ];
	block[ 6  ] = block[ 14 ];
	block[ 14 ] = temp;
}

static void ShiftRowsR(BYTE *block)
{
	BYTE temp;

	temp        = block[ 1  ];
	block[ 1  ] = block[ 13 ];
	block[ 13 ] = block[ 9  ];
	block[ 9  ] = block[ 5  ];
	block[ 5  ] = temp;

	temp        = block[ 2  ];
	block[ 2  ] = block[ 10 ];
	block[ 10 ] = temp;

	temp        = block[ 3  ];
	block[ 3  ] = block[ 7  ];
	block[ 7  ] = block[ 11 ];
	block[ 11 ] = block[ 15 ];
	block[ 15 ] = temp;

	temp        = block[ 6  ];
	block[ 6  ] = block[ 14 ];
	block[ 14 ] = temp;
}


__inline static BYTE Mul2(BYTE b)
{
	return (b << 1) ^ (b & 0x80 ? 0x1b : 0);
}

static void MixColumns(BYTE *block)
{
	unsigned int  i;

	for (i = 0; i < 16; i += 4)
	{
		BYTE b1 = block[ i     ];
		BYTE b2 = block[ i + 1 ];
		BYTE b3 = block[ i + 2 ];
		BYTE b4 = block[ i + 3 ];
		BYTE x  = b1 ^ b2 ^ b3 ^ b4;

		block[ i     ] ^= Mul2( b1 ^ b2 ) ^ x;
		block[ i + 1 ] ^= Mul2( b2 ^ b3 ) ^ x;
		block[ i + 2 ] ^= Mul2( b3 ^ b4 ) ^ x;
		block[ i + 3 ] ^= Mul2( b4 ^ b1 ) ^ x;
	}
}

static void MixColumnsR(BYTE *block)
{
	unsigned int  i;

	for (i = 0; i < 16; i += 4)
	{
		BYTE b1 = block[ i     ];
		BYTE b2 = block[ i + 1 ];
		BYTE b3 = block[ i + 2 ];
		BYTE b4 = block[ i + 3 ];
		BYTE q  = b1 ^ b2 ^ b3 ^ b4;
		BYTE p;

		q ^= Mul2( Mul2( Mul2(q) ) );
		p  = Mul2( Mul2( b1 ^ b3 ) ) ^ q;
		q ^= Mul2( Mul2( b2 ^ b4 ) );

		block[ i     ] ^= Mul2( b1 ^ b2 ) ^ p;
		block[ i + 1 ] ^= Mul2( b2 ^ b3 ) ^ q;
		block[ i + 2 ] ^= Mul2( b3 ^ b4 ) ^ p;
		block[ i + 3 ] ^= Mul2( b4 ^ b1 ) ^ q;
	}
}


static void SubBytes(BYTE *block)
{
	unsigned int  i;

	for (i = 0; i < 16; i++)
		block[i] = SBox[ block[i] ];
}

static void SubBytesR(BYTE *block)
{
	unsigned int  i;

	for (i = 0; i < 16; i++)
		block[i] = SBoxR[ block[i] ];
}

__inline static void AddRoundKey(BYTE *block, const DWORD *RKey)
{
	UAA32( block, 0 ) ^= RKey[0];
	UAA32( block, 1 ) ^= RKey[1];
	UAA32( block, 2 ) ^= RKey[2];
	UAA32( block, 3 ) ^= RKey[3];
}

static void AesCmacV4Block(BYTE *block)
{
	unsigned int i;

	for ( i = 0 ;;)
	{
		XorBlock(AesKeyV4 + i, block); i += AES_KEY_BYTES;
		SubBytes(block);
		XorBlock(AesKeyV4 + i, block); i += AES_KEY_BYTES;
		ShiftRows(block);

		if ( i >= 6 * AES_KEY_BYTES * 2 ) break;

		MixColumns(block);

		SubBytes(block);
		ShiftRows(block);
		MixColumns(block);
	}
}

void AesCmacV4(BYTE *Message, size_t MessageSize, BYTE *HashOut)
{
    int i;
    BYTE hash[AES_BLOCK_BYTES];

    memset(hash, 0, sizeof(hash));
    memset(Message + MessageSize, 0, AES_BLOCK_BYTES);
    Message[MessageSize] = 0x80;

    for (i = 0; i <= MessageSize; i += AES_BLOCK_BYTES)
    {
        XorBlock(Message + i, hash);
        AesCmacV4Block(hash);
    }

    memcpy(HashOut, hash, AES_BLOCK_BYTES);
}

__inline static DWORD SubDword(DWORD v)
{
	BYTE *b = (BYTE *)&v;

	b[0] = SBox[ b[0] ];
	b[1] = SBox[ b[1] ];
	b[2] = SBox[ b[2] ];
	b[3] = SBox[ b[3] ];

	return v;
}

void AesInitKey(AesCtx *Ctx, const BYTE *Key, BOOL IsV6)
{
	static const DWORD RCon[] = {
		0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
		0x20000000, 0x40000000, 0x80000000, 0x1B000000, 0x36000000 };

	unsigned int  i;
	DWORD  temp;

	memcpy(Ctx->Key, Key, AES_KEY_BYTES);

	for ( i = AES_KEY_DWORDS; i < ( AES_ROUNDS + 1 ) * 4; i++ )
	{
		temp = Ctx->Key[ i - 1 ];

		if ( ( i % AES_KEY_DWORDS ) == 0 )
			temp = BE32( SubDword( ROR32( BE32(temp), 24)  ) ^ RCon[ i / AES_KEY_DWORDS ] );

		Ctx->Key[ i ] = Ctx->Key[ i - AES_KEY_DWORDS ] ^ temp;
	}

	if ( IsV6 )
	{
		BYTE *_p = (BYTE *)Ctx->Key;

		_p[ 4 * 16 ] ^= 0x73;
		_p[ 6 * 16 ] ^= 0x09;
		_p[ 8 * 16 ] ^= 0xE4;
	}
}


void AesEncryptBlock(AesCtx *Ctx, BYTE *block)
{
	unsigned int  i;

	for ( i = 0 ;; i += 4 )
	{
		AddRoundKey(block, &Ctx->Key[ i ]);
		SubBytes(block);
		ShiftRows(block);

		if ( i >= ( AES_ROUNDS - 1 ) * 4 ) break;

		MixColumns(block);
	}

	AddRoundKey(block, &Ctx->Key[ AES_ROUNDS * 4 ]);
}

void AesDecryptBlock(AesCtx *Ctx, BYTE *block)
{
	unsigned int  i;

	AddRoundKey(block, &Ctx->Key[ AES_ROUNDS * 4 ]);

	for ( i = ( AES_ROUNDS - 1 ) * 4 ;; i -= 4 )
	{
		ShiftRowsR(block);
		SubBytesR(block);
		AddRoundKey(block, &Ctx->Key[ i ]);

		if ( i == 0 ) break;

		MixColumnsR(block);
	}
}


void AesEncryptCbc(AesCtx *Ctx, BYTE *iv, BYTE *data, size_t *len)
{
	// Pad up to blocksize inclusive
	unsigned int  pad = (~*len & 15) + 1;
	memset(data + *len, pad, pad);
	*len += pad;

	if ( iv ) XorBlock(iv, data);
	AesEncryptBlock(Ctx, data);

	size_t i;

	for (i = *len - 16; i; i -= 16)
	{
		XorBlock(data, data + 16);
		data += 16;
		AesEncryptBlock(Ctx, data);
	}
}

void AesDecryptCbc(AesCtx *Ctx, BYTE *iv, BYTE *data, size_t len)
{
	BYTE  *cc;

	for (cc = data + len - 16; cc > data; cc -= 16)
	{
		AesDecryptBlock(Ctx, cc);
		XorBlock(cc - 16, cc);
	}

	AesDecryptBlock(Ctx, cc);
	if ( iv ) XorBlock(iv, cc);
}