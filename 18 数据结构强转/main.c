#include <stdio.h>
#include <string.h>

#pragma pack(push)  // save the pack status
#pragma pack(1)     // 1 byte align

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

#define IOT_MAC_ADDR_LEN 6

typedef struct _ge_frm_hdr_t {
	/* preable code 0xAAAA */
	uint16_t preamble;
	/* data length range:[0x80,0x88] */
	uint8_t  data_len;
	/* function code */
	uint8_t  fn;
}  ge_frm_hdr_t;

typedef struct _ge_extend_fn_hdr_t {
	ge_frm_hdr_t  hdr;
	/* sub function code */
	uint8_t  subfn;
}  ge_extend_fn_hdr_t;

typedef struct _ge_frame_aes_set_subfn163_t {
	ge_extend_fn_hdr_t  hdr;
	uint8_t             dest_mac[IOT_MAC_ADDR_LEN];
//	uint8_t				resv;
	uint8_t             enable : 1,
						key_type : 1,
						key_bits : 2,
						mode : 2,
						resv_bit : 2;
	uint8_t             key[16];
} ge_frame_aes_set_subfn163_t;

typedef struct _ge_aes_contxt_t {
	/* whether to enable aes encryption */
//	uint8_t resv;
	uint8_t enable : 1,
			/* key select 0->ge_key, 1->user_key */
			key_type : 1,
			/* the secret key type, 0->128, 1->192, 2->256 */
			key_bits : 2,
			/* the secret key type, 0->ECB, 1->CBC, 2->CTR */
			mode : 2,
			/* in order to align */
			resv_bit : 2;
	/* pass-through data(FE A0) using the secret key */
	uint8_t key[16];
}ge_aes_contxt_t;

//ge_frame_aes_set_subfn163_t g_subfn163 = {0xAA,0xaa,0x28,0xfe,0xa3, 0x01,0x02,0x03,0x04,0x05,0x06, 0x23,  0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd };	//0b00100011
uint8_t data[29] = { 0xAA,0xaa,0x28,0xfe,0xa3, 0x01,0x02,0x03,0x04,0x05,0x06, 0x00,0x23,  0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd,0xa,0xb,0xc,0xd };
ge_frame_aes_set_subfn163_t* g_subfn163 = &data;
int main()
{
	printf("%x,%x,%x,%x \n", g_subfn163->hdr.hdr.preamble, g_subfn163->hdr.hdr.data_len, g_subfn163->hdr.hdr.fn, g_subfn163->hdr.subfn);

	printf("mac:");
	for (uint8_t i = 0; i < 6; i++)
	{
		printf("%x ", g_subfn163->dest_mac[i]);
	}
	printf("\n");

	printf("enable:%d,type:%d,bit:%d,mode:%d,resv:%d \n",
		g_subfn163->enable, g_subfn163->key_type, g_subfn163->key_bits, g_subfn163->mode, g_subfn163->resv_bit);

	printf("key:");
	for (uint8_t i = 0; i < 16; i++)
	{
		printf("%x ",g_subfn163->key[i]);
	}
	printf("\n");
	printf("enable addr:%x\n",&g_subfn163->key);
	printf("-------------------------------------------------------------\n");

	//ge_aes_contxt_t* ge = (g_subfn163 + (sizeof(g_subfn163->dest_mac)));
	//ge_aes_contxt_t* ge = &g_subfn163->resv;
	//ge_aes_contxt_t *ge = (ge_aes_contxt_t*)g_subfn163->resv;
	ge_aes_contxt_t ge_a;
	ge_aes_contxt_t* ge = &ge_a;
	memcpy(ge, &g_subfn163->enable, sizeof(ge_aes_contxt_t));

	printf("enable:%d,type:%d,bit:%d,mode:%d,resv:%d \n",
		ge->enable, ge->key_type, ge->key_bits, ge->mode, ge->resv_bit);

	printf("key:");
	for (uint8_t i = 0; i < 16; i++)
	{
		printf("%x ", ge->key[i]);
	}
	printf("\n");
	printf("enable addr:%x\n", &ge->key);

	getchar();
	return 0;
}

#pragma pack(pop)