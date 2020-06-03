/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../../../rrc_15.5.1_asn.asn1"
 * 	`asn1c -D ./rrc_out_hlal -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "RRCReconfigurationComplete-IEs.h"

#include "RRCReconfigurationComplete-v1530-IEs.h"
asn_TYPE_member_t asn_MBR_RRCReconfigurationComplete_IEs_1[] = {
	{ ATF_POINTER, 2, offsetof(struct RRCReconfigurationComplete_IEs, lateNonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"lateNonCriticalExtension"
		},
	{ ATF_POINTER, 1, offsetof(struct RRCReconfigurationComplete_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RRCReconfigurationComplete_v1530_IEs,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nonCriticalExtension"
		},
};
static const int asn_MAP_RRCReconfigurationComplete_IEs_oms_1[] = { 0, 1 };
static const ber_tlv_tag_t asn_DEF_RRCReconfigurationComplete_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RRCReconfigurationComplete_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* lateNonCriticalExtension */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtension */
};
asn_SEQUENCE_specifics_t asn_SPC_RRCReconfigurationComplete_IEs_specs_1 = {
	sizeof(struct RRCReconfigurationComplete_IEs),
	offsetof(struct RRCReconfigurationComplete_IEs, _asn_ctx),
	asn_MAP_RRCReconfigurationComplete_IEs_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_RRCReconfigurationComplete_IEs_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RRCReconfigurationComplete_IEs = {
	"RRCReconfigurationComplete-IEs",
	"RRCReconfigurationComplete-IEs",
	&asn_OP_SEQUENCE,
	asn_DEF_RRCReconfigurationComplete_IEs_tags_1,
	sizeof(asn_DEF_RRCReconfigurationComplete_IEs_tags_1)
		/sizeof(asn_DEF_RRCReconfigurationComplete_IEs_tags_1[0]), /* 1 */
	asn_DEF_RRCReconfigurationComplete_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_RRCReconfigurationComplete_IEs_tags_1)
		/sizeof(asn_DEF_RRCReconfigurationComplete_IEs_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RRCReconfigurationComplete_IEs_1,
	2,	/* Elements count */
	&asn_SPC_RRCReconfigurationComplete_IEs_specs_1	/* Additional specs */
};

