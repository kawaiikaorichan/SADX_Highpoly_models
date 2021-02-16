#include "SADXModLoader.h"
#include <stdio.h>
#include "IniFile.hpp"
#include "pch.h"
#include <cmath>
#include "stdafx.h"
#include "OBJECT_Finger.h"

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

//Options
enum SuperSText { Dreamcast, Upgraded };

static int SSText = Upgraded;

extern "C"
{
	uint16_t Sonic_RightUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Sonic_RightLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Sonic_LeftUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Sonic_LeftLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Sonic_RightKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Sonic_RightLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Sonic_LeftKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Sonic_LeftLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Sonic_RightShoeIndices_DX[] = {
		177, 461,
		297, 459,
		298, 458,
		331, 473,
		317, 469,
		290, 420,
		391, 422,
		292, 430,
		349, 507,
		193, 509,
		194, 529,
		195, 531,
		200, 535,
		201, 537,
		116, 276,
		108, 235,
		109, 234,
		110, 233,
		135, 222,
		136, 223,
		27, 215,
		28, 214,
		25, 213,
		85, 262,
		86, 261,
		91, 265,
		92, 263,
		18, 199,
		19, 198,
		20, 197,
		79, 13,
		80, 11,
		212, 527,
		213, 523,
		206, 555,
		207, 557,
		175, 513,
		176, 511,
	};

	uint16_t Sonic_LeftShoeIndices_DX[] = {
		205, 533,
		206, 530,
		199, 559,
		200, 560,
		168, 519,
		169, 517,
		170, 467,
		290, 465,
		291, 463,
		324, 479,
		310, 475,
		283, 427,
		284, 428,
		285, 436,
		342, 514,
		186, 515,
		187, 536,
		188, 537,
		193, 542,
		194, 543,
		112, 18,
		113, 281,
		105, 239,
		106, 238,
		107, 237,
		132, 226,
		133, 227,
		24, 219,
		25, 218,
		26, 217,
		82, 268,
		83, 267,
		88, 270,
		89, 269,
		15, 203,
		16, 202,
		17, 201,
		76, 12,
		77, 241,
	};

	uint16_t Sonic_RightHandIndices_DX[] = {
		11, 50,
		58, 139,
		59, 138,
		60, 137,
		0, 14,
		67, 127,
		68, 126,
		69, 125,
		12, 13,
		34, 298,
		35, 297,
		36, 296,
		1, 55,
		28, 490,
		29, 489,
		30, 488,
		5, 54,
		19, 571,
		20, 570,
		21, 569,
		8, 12,
		37, 541,
		38, 540,
		39, 539,
		4, 15,
		46, 466,
		47, 465,
		48, 464,
	};

	uint16_t Sonic_LeftHandIndices_DX[] = {
		11, 50,
		61, 395,
		62, 210,
		63, 547,
		4, 15,
		64, 253,
		65, 68,
		66, 405,
		8, 12,
		22, 319,
		23, 134,
		24, 471,
		5, 54,
		31, 381,
		32, 196,
		33, 533,
		1, 55,
		34, 348,
		35, 163,
		36, 500,
		12, 13,
		40, 266,
		41, 81,
		42, 418,
		0, 14,
		52, 389,
		53, 204,
		51, 541,
	};

	uint16_t Sonic_LeftLightIndices_DX[] = {
		324, 479,
		310, 475,
		283, 427,
		284, 428,
		285, 436,
		342, 514,
		186, 515,
		187, 536,
		188, 537,
		193, 542,
		194, 543,
		112, 18,
		113, 281,
		105, 239,
		106, 238,
		107, 237,
		132, 226,
		133, 227,
		24, 219,
		25, 218,
		26, 217,
		82, 268,
		83, 267,
		88, 270,
		89, 269,
		15, 203,
		16, 202,
		17, 201,
		76, 12,
		77, 11,
		205, 533,
		206, 531,
		199, 527,
		200, 525,
		168, 519,
		169, 517,
		170, 467,
		290, 465,
		291, 463,
	};

	uint16_t Sonic_RightLightIndices_DX[] = {
		324, 476,
		291, 461,
		290, 462,
		170, 464,
		169, 514,
		168, 516,
		200, 522,
		199, 524,
		206, 528,
		205, 530,
		77, 11,
		76, 13,
		17, 200,
		16, 201,
		15, 202,
		89, 266,
		88, 268,
		83, 264,
		82, 265,
		26, 216,
		25, 217,
		24, 218,
		133, 226,
		132, 225,
		107, 236,
		106, 237,
		105, 238,
		113, 278,
		112, 19,
		194, 540,
		193, 538,
		188, 534,
		187, 532,
		186, 512,
		342, 510,
		285, 433,
		284, 425,
		283, 423,
		310, 472,
	};

	uint16_t Sonic_WristRingIndices_DX[] = {
		4, 456,
		5, 457,
		1, 453,
		0, 452,
	};

	uint16_t SSonic_RightLowerArmIndices_DX[] = {
		4, 468,
		5, 649,
		1, 465,
		0, 644,
	};

	uint16_t SSonic_RightLegIndices_DX[] = {
		0, 660,
		1, 661,
		4, 664,
		5, 665,
	};

	uint16_t SSonic_RightHandIndices_DX[] = {
	11, 50,
	58, 418,
	59, 417,
	60, 416,
	0, 14,
	67, 157,
	68, 156,
	69, 155,
	12, 13,
	13, 163,
	14, 162,
	15, 161,
	1, 55,
	19, 376,
	20, 375,
	21, 374,
	5, 54,
	28, 289,
	29, 288,
	30, 287,
	8, 12,
	37, 487,
	38, 486,
	39, 485,
	4, 15,
	46, 481,
	47, 480,
	48, 479,
	};

	uint16_t SSonic_LeftHandIndices_DX[] = {
	11, 50,
	61, 412,
	62, 411,
	63, 410,
	4, 15,
	64, 82,
	65, 81,
	66, 80,
	8, 12,
	28, 211,
	29, 210,
	30, 209,
	5, 54,
	19, 232,
	20, 231,
	21, 230,
	1, 55,
	16, 475,
	17, 474,
	18, 473,
	12, 13,
	40, 154,
	41, 153,
	42, 152,
	0, 14,
	52, 349,
	53, 348,
	54, 347,
	};

	void __cdecl InitSonicWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebp@1
		NJS_OBJECT* v4; // edi@1
		NJS_OBJECT* v5; // eax@1

		//The following welds are for Sonic
		SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
		SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
		SonicWeldInfo[0].anonymous_5 = 0;
		SonicWeldInfo[0].VertexBuffer = 0;
		SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightUpperArmIndices_DX) / 2);
		SonicWeldInfo[0].WeldType = 2;
		SonicWeldInfo[0].VertIndexes = Sonic_RightUpperArmIndices_DX;
		SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
		SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
		SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLowerArmIndices_DX) / 2);
		SonicWeldInfo[1].WeldType = 2;
		SonicWeldInfo[1].anonymous_5 = 0;
		SonicWeldInfo[1].VertexBuffer = 0;
		SonicWeldInfo[1].VertIndexes = Sonic_RightLowerArmIndices_DX;
		SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
		SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
		SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftUpperArmIndices_DX) / 2);
		SonicWeldInfo[2].WeldType = 2;
		SonicWeldInfo[2].anonymous_5 = 0;
		SonicWeldInfo[2].VertexBuffer = 0;
		SonicWeldInfo[2].VertIndexes = Sonic_LeftUpperArmIndices_DX;
		SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
		v0 = SONIC_OBJECTS[9];
		SonicWeldInfo[3].VertIndexes = Sonic_LeftLowerArmIndices_DX;
		SonicWeldInfo[3].ModelB = v0;
		SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLowerArmIndices_DX) / 2);
		SonicWeldInfo[3].WeldType = 2;
		SonicWeldInfo[3].anonymous_5 = 0;
		SonicWeldInfo[3].VertexBuffer = 0;
		SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
		SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
		SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightKneeIndices_DX) / 2);
		SonicWeldInfo[4].WeldType = 2;
		SonicWeldInfo[4].anonymous_5 = 0;
		SonicWeldInfo[4].VertexBuffer = 0;
		SonicWeldInfo[4].VertIndexes = Sonic_RightKneeIndices_DX;
		SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
		SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
		SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLegIndices_DX) / 2);
		SonicWeldInfo[5].WeldType = 2;
		SonicWeldInfo[5].anonymous_5 = 0;
		SonicWeldInfo[5].VertexBuffer = 0;
		SonicWeldInfo[5].VertIndexes = Sonic_RightLegIndices_DX;
		SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
		v1 = SONIC_OBJECTS[18];
		SonicWeldInfo[6].VertIndexes = Sonic_LeftKneeIndices_DX;
		SonicWeldInfo[6].ModelB = v1;
		SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftKneeIndices_DX) / 2);
		SonicWeldInfo[6].WeldType = 2;
		SonicWeldInfo[6].anonymous_5 = 0;
		SonicWeldInfo[6].VertexBuffer = 0;
		SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
		SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
		SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLegIndices_DX) / 2);
		SonicWeldInfo[7].WeldType = 2;
		SonicWeldInfo[7].anonymous_5 = 0;
		SonicWeldInfo[7].VertexBuffer = 0;
		SonicWeldInfo[7].VertIndexes = Sonic_LeftLegIndices_DX;
		SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
		SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
		SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightShoeIndices_DX) / 2);
		SonicWeldInfo[8].WeldType = 2;
		SonicWeldInfo[8].anonymous_5 = 0;
		SonicWeldInfo[8].VertexBuffer = 0;
		SonicWeldInfo[8].VertIndexes = Sonic_RightShoeIndices_DX;
		SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
		v2 = SONIC_OBJECTS[21];
		SonicWeldInfo[9].VertIndexes = Sonic_LeftShoeIndices_DX;
		SonicWeldInfo[9].ModelB = v2;
		SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftShoeIndices_DX) / 2);
		SonicWeldInfo[9].WeldType = 2;
		SonicWeldInfo[9].anonymous_5 = 0;
		SonicWeldInfo[9].VertexBuffer = 0;

		SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[11].ModelA = SONIC_OBJECTS[10];
		SonicWeldInfo[11].ModelB = SONIC_OBJECTS[11];
		SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftHandIndices_DX) / 2);
		SonicWeldInfo[11].WeldType = 2;
		SonicWeldInfo[11].anonymous_5 = 0;
		SonicWeldInfo[11].VertexBuffer = 0;
		SonicWeldInfo[11].VertIndexes = Sonic_LeftHandIndices_DX;
		SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
		SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
		SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLightIndices_DX) / 2);
		SonicWeldInfo[12].WeldType = 2;
		SonicWeldInfo[12].anonymous_5 = 0;
		SonicWeldInfo[12].VertexBuffer = 0;
		SonicWeldInfo[12].VertIndexes = Sonic_LeftLightIndices_DX;
		SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
		SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
		SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLightIndices_DX) / 2);
		SonicWeldInfo[13].WeldType = 2;
		SonicWeldInfo[13].anonymous_5 = 0;
		SonicWeldInfo[13].VertexBuffer = 0;
		SonicWeldInfo[13].VertIndexes = Sonic_RightLightIndices_DX;
		SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
		SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
		SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_WristRingIndices_DX) / 2);
		SonicWeldInfo[14].WeldType = 2;
		SonicWeldInfo[14].anonymous_5 = 0;
		SonicWeldInfo[14].VertexBuffer = 0;
		SonicWeldInfo[14].VertIndexes = Sonic_WristRingIndices_DX;
		SonicWeldInfo[15].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[15].ModelA = SONIC_OBJECTS[5];
		SonicWeldInfo[15].ModelB = 0;
		SonicWeldInfo[15].VertexPairCount = 2;
		SonicWeldInfo[15].WeldType = 4;
		SonicWeldInfo[15].anonymous_5 = 0;
		SonicWeldInfo[15].VertexBuffer = 0;
		SonicWeldInfo[15].VertIndexes = 0;
		SonicWeldInfo[16].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[16].ModelA = SONIC_OBJECTS[11];
		SonicWeldInfo[16].ModelB = 0;
		SonicWeldInfo[16].VertexPairCount = 2;
		SonicWeldInfo[16].WeldType = 5;
		SonicWeldInfo[16].anonymous_5 = 0;
		SonicWeldInfo[16].VertexBuffer = 0;
		SonicWeldInfo[16].VertIndexes = 0;
		SonicWeldInfo[17].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[17].ModelA = SONIC_OBJECTS[59];
		SonicWeldInfo[17].ModelB = 0;
		SonicWeldInfo[17].VertexPairCount = 0;
		SonicWeldInfo[17].WeldType = 7;
		SonicWeldInfo[17].anonymous_5 = 0;
		SonicWeldInfo[17].VertexBuffer = 0;
		SonicWeldInfo[17].VertIndexes = 0;
		SonicWeldInfo[18].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[18].ModelA = SONIC_OBJECTS[61];
		SonicWeldInfo[18].ModelB = 0;
		SonicWeldInfo[18].VertexPairCount = 0;
		SonicWeldInfo[18].WeldType = 6;
		SonicWeldInfo[18].anonymous_5 = 0;
		SonicWeldInfo[18].VertexBuffer = 0;
		SonicWeldInfo[18].VertIndexes = 0;
		SonicWeldInfo[19].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[19].ModelA = SONIC_OBJECTS[16];
		SonicWeldInfo[19].ModelB = 0;
		SonicWeldInfo[19].VertexPairCount = 0;
		SonicWeldInfo[19].WeldType = 6;
		SonicWeldInfo[19].anonymous_5 = 0;
		SonicWeldInfo[19].VertexBuffer = 0;
		SonicWeldInfo[19].VertIndexes = 0;
		SonicWeldInfo[20].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[20].ModelA = SONIC_OBJECTS[21];
		SonicWeldInfo[20].ModelB = 0;
		SonicWeldInfo[20].VertexPairCount = 0;
		SonicWeldInfo[20].WeldType = 7;
		SonicWeldInfo[20].anonymous_5 = 0;
		SonicWeldInfo[20].VertexBuffer = 0;
		SonicWeldInfo[20].VertIndexes = 0;
		SonicWeldInfo[21].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[21].ModelA = SONIC_OBJECTS[45];
		SonicWeldInfo[21].ModelB = 0;
		SonicWeldInfo[21].VertexPairCount = 0;
		SonicWeldInfo[21].WeldType = 8;
		SonicWeldInfo[21].anonymous_5 = 0;
		SonicWeldInfo[21].VertexBuffer = 0;
		SonicWeldInfo[21].VertIndexes = 0;

		//The following welds are for Super Sonic
		SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
		SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
		SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightUpperArmIndices_DX) / 2);
		SonicWeldInfo[22].WeldType = 2;
		SonicWeldInfo[22].anonymous_5 = 0;
		SonicWeldInfo[22].VertexBuffer = 0;
		SonicWeldInfo[22].VertIndexes = Sonic_RightUpperArmIndices_DX;
		SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
		SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
		SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(SSonic_RightLowerArmIndices_DX) / 2);
		SonicWeldInfo[23].WeldType = 2;
		SonicWeldInfo[23].anonymous_5 = 0;
		SonicWeldInfo[23].VertexBuffer = 0;
		SonicWeldInfo[23].VertIndexes = SSonic_RightLowerArmIndices_DX;
		SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
		SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
		SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftUpperArmIndices_DX) / 2);
		SonicWeldInfo[24].WeldType = 2;
		SonicWeldInfo[24].anonymous_5 = 0;
		SonicWeldInfo[24].VertexBuffer = 0;
		SonicWeldInfo[24].VertIndexes = Sonic_LeftUpperArmIndices_DX;
		SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
		SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
		SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLowerArmIndices_DX) / 2);
		SonicWeldInfo[25].WeldType = 2;
		SonicWeldInfo[25].anonymous_5 = 0;
		SonicWeldInfo[25].VertexBuffer = 0;
		SonicWeldInfo[25].VertIndexes = Sonic_LeftLowerArmIndices_DX;
		SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
		SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
		SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightKneeIndices_DX) / 2);
		SonicWeldInfo[26].WeldType = 2;
		SonicWeldInfo[26].anonymous_5 = 0;
		SonicWeldInfo[26].VertexBuffer = 0;
		SonicWeldInfo[26].VertIndexes = Sonic_RightKneeIndices_DX;
		SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
		SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
		SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(SSonic_RightLegIndices_DX) / 2);
		SonicWeldInfo[27].WeldType = 2;
		SonicWeldInfo[27].anonymous_5 = 0;
		SonicWeldInfo[27].VertexBuffer = 0;
		SonicWeldInfo[27].VertIndexes = SSonic_RightLegIndices_DX;
		SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
		v3 = SONIC_OBJECTS[39];
		SonicWeldInfo[28].VertIndexes = Sonic_LeftKneeIndices_DX;
		SonicWeldInfo[28].ModelB = v3;
		SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftKneeIndices_DX) / 2);
		SonicWeldInfo[28].WeldType = 2;
		SonicWeldInfo[28].anonymous_5 = 0;
		SonicWeldInfo[28].VertexBuffer = 0;
		SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
		SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
		SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLegIndices_DX) / 2);
		SonicWeldInfo[29].WeldType = 2;
		SonicWeldInfo[29].anonymous_5 = 0;
		SonicWeldInfo[29].VertexBuffer = 0;
		SonicWeldInfo[29].VertIndexes = Sonic_LeftLegIndices_DX;
		SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
		SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
		SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLightIndices_DX) / 2);
		SonicWeldInfo[30].WeldType = 2;
		SonicWeldInfo[30].anonymous_5 = 0;
		SonicWeldInfo[30].VertexBuffer = 0;
		SonicWeldInfo[30].VertIndexes = Sonic_RightLightIndices_DX;
		SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
		SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
		SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLightIndices_DX) / 2);
		SonicWeldInfo[31].WeldType = 2;
		SonicWeldInfo[31].anonymous_5 = 0;
		SonicWeldInfo[31].VertexBuffer = 0;
		SonicWeldInfo[31].VertIndexes = Sonic_LeftLightIndices_DX;
		SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
		SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
		SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(SSonic_LeftHandIndices_DX) / 2);
		SonicWeldInfo[32].WeldType = 2;
		SonicWeldInfo[32].anonymous_5 = 0;
		SonicWeldInfo[32].VertexBuffer = 0;
		SonicWeldInfo[32].VertIndexes = SSonic_LeftHandIndices_DX;
		SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
		v4 = SONIC_OBJECTS[27];
		SonicWeldInfo[33].anonymous_5 = 0;
		SonicWeldInfo[33].VertexBuffer = 0;
		SonicWeldInfo[33].VertIndexes = SSonic_RightHandIndices_DX;
		SonicWeldInfo[33].ModelB = v4;
		SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(SSonic_RightHandIndices_DX) / 2);
		SonicWeldInfo[33].WeldType = 2;
		SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
		SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
		SonicWeldInfo[34].anonymous_5 = 0;
		SonicWeldInfo[34].VertexBuffer = 0;
		SonicWeldInfo[34].VertexPairCount = 4;
		SonicWeldInfo[34].VertIndexes = SSonic_LeftHandIndices_DX;
		SonicWeldInfo[34].WeldType = 2;
		SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
		v5 = SONIC_OBJECTS[27];
		SonicWeldInfo[35].anonymous_5 = 0;
		SonicWeldInfo[35].VertexBuffer = 0;
		SonicWeldInfo[36].BaseModel = 0;
		SonicWeldInfo[36].ModelA = 0;
		SonicWeldInfo[36].ModelB = 0;
		SonicWeldInfo[35].VertIndexes = SSonic_RightHandIndices_DX;
		SonicWeldInfo[36].VertexPairCount = 0;
		SonicWeldInfo[36].VertexBuffer = 0;
		SonicWeldInfo[35].VertexPairCount = 4;
		SonicWeldInfo[35].ModelB = v5;
		SonicWeldInfo[35].WeldType = 2;
		SonicWeldInfo[36].VertIndexes = 0;
	}

	void __cdecl InitNPCSonicWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebp@1
		NJS_OBJECT* v4; // eax@1

		NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
		NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
		NPCSonicWeldInfo[0].anonymous_5 = 0;
		NPCSonicWeldInfo[0].VertexBuffer = 0;
		NPCSonicWeldInfo[0].VertIndexes = Sonic_RightUpperArmIndices_DX;
		NPCSonicWeldInfo[0].WeldType = 2;
		NPCSonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightUpperArmIndices_DX) / 2);
		NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
		NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
		NPCSonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLowerArmIndices_DX) / 2);
		NPCSonicWeldInfo[1].WeldType = 2;
		NPCSonicWeldInfo[1].anonymous_5 = 0;
		NPCSonicWeldInfo[1].VertexBuffer = 0;
		NPCSonicWeldInfo[1].VertIndexes = Sonic_RightLowerArmIndices_DX;
		NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
		NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
		NPCSonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftUpperArmIndices_DX) / 2);
		NPCSonicWeldInfo[2].WeldType = 2;
		NPCSonicWeldInfo[2].anonymous_5 = 0;
		NPCSonicWeldInfo[2].VertexBuffer = 0;
		NPCSonicWeldInfo[2].VertIndexes = Sonic_LeftUpperArmIndices_DX;
		NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
		v0 = SONIC_OBJECTS[9];
		NPCSonicWeldInfo[3].VertIndexes = Sonic_LeftLowerArmIndices_DX;
		NPCSonicWeldInfo[3].ModelB = v0;
		NPCSonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLowerArmIndices_DX) / 2);
		NPCSonicWeldInfo[3].WeldType = 2;
		NPCSonicWeldInfo[3].anonymous_5 = 0;
		NPCSonicWeldInfo[3].VertexBuffer = 0;
		NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
		NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
		NPCSonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightKneeIndices_DX) / 2);
		NPCSonicWeldInfo[4].WeldType = 2;
		NPCSonicWeldInfo[4].anonymous_5 = 0;
		NPCSonicWeldInfo[4].VertexBuffer = 0;
		NPCSonicWeldInfo[4].VertIndexes = Sonic_RightKneeIndices_DX;
		NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
		NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
		NPCSonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLegIndices_DX) / 2);
		NPCSonicWeldInfo[5].WeldType = 2;
		NPCSonicWeldInfo[5].anonymous_5 = 0;
		NPCSonicWeldInfo[5].VertexBuffer = 0;
		NPCSonicWeldInfo[5].VertIndexes = Sonic_RightLegIndices_DX;
		NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
		NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
		NPCSonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftKneeIndices_DX) / 2);
		NPCSonicWeldInfo[6].WeldType = 2;
		NPCSonicWeldInfo[6].anonymous_5 = 0;
		NPCSonicWeldInfo[6].VertexBuffer = 0;
		NPCSonicWeldInfo[6].VertIndexes = Sonic_LeftKneeIndices_DX;
		NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
		v1 = SONIC_OBJECTS[19];
		NPCSonicWeldInfo[7].VertIndexes = Sonic_LeftLegIndices_DX;
		NPCSonicWeldInfo[7].ModelB = v1;
		NPCSonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLegIndices_DX) / 2);
		NPCSonicWeldInfo[7].WeldType = 2;
		NPCSonicWeldInfo[7].anonymous_5 = 0;
		NPCSonicWeldInfo[7].VertexBuffer = 0;
		NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
		NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
		NPCSonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightShoeIndices_DX) / 2);
		NPCSonicWeldInfo[8].WeldType = 2;
		NPCSonicWeldInfo[8].anonymous_5 = 0;
		NPCSonicWeldInfo[8].VertexBuffer = 0;
		NPCSonicWeldInfo[8].VertIndexes = Sonic_RightShoeIndices_DX;
		NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
		v2 = SONIC_OBJECTS[21];
		NPCSonicWeldInfo[9].VertIndexes = Sonic_LeftShoeIndices_DX;
		NPCSonicWeldInfo[9].ModelB = v2;
		NPCSonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftShoeIndices_DX) / 2);
		NPCSonicWeldInfo[9].WeldType = 2;
		NPCSonicWeldInfo[9].anonymous_5 = 0;
		NPCSonicWeldInfo[9].VertexBuffer = 0;
		NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
		NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
		NPCSonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftHandIndices_DX) / 2);
		NPCSonicWeldInfo[10].WeldType = 2;
		NPCSonicWeldInfo[10].anonymous_5 = 0;
		NPCSonicWeldInfo[10].VertexBuffer = 0;
		NPCSonicWeldInfo[10].VertIndexes = Sonic_LeftHandIndices_DX;

		NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
		NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
		NPCSonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightLightIndices_DX) / 2);
		NPCSonicWeldInfo[12].anonymous_5 = 0;
		NPCSonicWeldInfo[12].VertexBuffer = 0;
		NPCSonicWeldInfo[12].WeldType = 2;
		NPCSonicWeldInfo[12].VertIndexes = Sonic_RightLightIndices_DX;
		NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
		v3 = SONIC_OBJECTS[61];
		NPCSonicWeldInfo[13].anonymous_5 = 0;
		NPCSonicWeldInfo[13].VertexBuffer = 0;
		NPCSonicWeldInfo[13].ModelB = v3;
		NPCSonicWeldInfo[13].VertIndexes = Sonic_LeftLightIndices_DX;
		NPCSonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LeftLightIndices_DX) / 2);
		NPCSonicWeldInfo[13].WeldType = 2;
		NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
		v4 = SONIC_OBJECTS[63];
		NPCSonicWeldInfo[14].anonymous_5 = 0;
		NPCSonicWeldInfo[14].VertexBuffer = 0;
		NPCSonicWeldInfo[15].BaseModel = 0;
		NPCSonicWeldInfo[15].ModelA = 0;
		NPCSonicWeldInfo[15].ModelB = 0;
		NPCSonicWeldInfo[15].VertexPairCount = 0;
		NPCSonicWeldInfo[15].VertexBuffer = 0;
		NPCSonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_WristRingIndices_DX) / 2);
		NPCSonicWeldInfo[14].ModelB = v4;
		NPCSonicWeldInfo[14].WeldType = 2;
		NPCSonicWeldInfo[14].VertIndexes = Sonic_WristRingIndices_DX;
		NPCSonicWeldInfo[15].VertIndexes = 0;
	}

	uint16_t Amy_RightUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Amy_RightLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Amy_LeftUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Amy_LeftLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Amy_RightKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Amy_RightLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Amy_LeftKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Amy_LeftLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Amy_RightShoeIndices_DX[] = {
		91, 231,
		90, 228,
		214, 119,
		215, 120,
		241, 105,
		240, 62,
		249, 61,
		250, 139,
		265, 142,
		264, 144,
		378, 251,
		362, 240,
		361, 238,
		49, 28,
		44, 29,
		26, 24,
		25, 23,
		261, 183,
		259, 181,
		377, 261,
		366, 176,
		297, 175,
		296, 90,
		306, 89,
		304, 91,
		324, 107,
		322, 109,
		187, 114,
		188, 224,
	};

	uint16_t Amy_LeftShoeIndices_DX[] = {
		92, 231,
		188, 224,
		187, 114,
		323, 109,
		324, 108,
		305, 91,
		306, 89,
		296, 90,
		297, 175,
		366, 176,
		377, 261,
		260, 181,
		261, 182,
		25, 23,
		26, 24,
		44, 30,
		49, 28,
		361, 238,
		362, 239,
		378, 251,
		264, 144,
		266, 143,
		250, 139,
		249, 60,
		240, 62,
		241, 105,
		215, 120,
		214, 119,
		90, 228,
	};

	uint16_t Amy_RightHandIndices_DX[] = {
		11, 50,
		51, 386,
		50, 387,
		49, 388,
		4, 15,
		39, 380,
		38, 381,
		37, 382,
		8, 12,
		30, 509,
		29, 510,
		28, 511,
		5, 54,
		21, 143,
		20, 144,
		19, 145,
		1, 55,
		15, 365,
		14, 366,
		13, 367,
		12, 13,
		69, 83,
		68, 84,
		67, 85,
		0, 14,
		60, 95,
		59, 96,
		58, 97,
	};

	uint16_t Amy_LeftHandIndices_DX[] = {
		11, 50,
		57, 509,
		56, 510,
		55, 511,
		0, 14,
		66, 119,
		65, 120,
		64, 121,
		12, 13,
		18, 113,
		17, 114,
		16, 115,
		1, 55,
		21, 455,
		20, 456,
		19, 457,
		5, 54,
		30, 203,
		29, 204,
		28, 205,
		8, 12,
		39, 290,
		38, 291,
		37, 292,
		4, 15,
		48, 95,
		47, 96,
		46, 97,
	};


	void __cdecl InitAmyWeldInfo_mod()
	{
		NJS_OBJECT* v0; // edi@1
		NJS_OBJECT* v1; // edi@1
		NJS_OBJECT* v2; // edi@1
		NJS_OBJECT* v3; // edi@1
		NJS_OBJECT* v4; // esi@1
		NJS_OBJECT* v5; // edx@1
		NJS_OBJECT* v6; // edx@1
		NJS_OBJECT* v7; // eax@1

		AmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
		AmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
		AmyWeldInfo[0].anonymous_5 = 0;
		AmyWeldInfo[0].VertexBuffer = 0;
		AmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightUpperArmIndices_DX) / 2);
		AmyWeldInfo[0].WeldType = 2;
		AmyWeldInfo[0].VertIndexes = Amy_RightUpperArmIndices_DX;
		AmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
		AmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
		AmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightLowerArmIndices_DX) / 2);
		AmyWeldInfo[1].WeldType = 2;
		AmyWeldInfo[1].anonymous_5 = 0;
		AmyWeldInfo[1].VertexBuffer = 0;
		AmyWeldInfo[1].VertIndexes = Amy_RightLowerArmIndices_DX;
		AmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
		AmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
		AmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftUpperArmIndices_DX) / 2);
		AmyWeldInfo[2].WeldType = 2;
		AmyWeldInfo[2].anonymous_5 = 0;
		AmyWeldInfo[2].VertexBuffer = 0;
		AmyWeldInfo[2].VertIndexes = Amy_LeftUpperArmIndices_DX;
		AmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
		v0 = AMY_OBJECTS[11];
		AmyWeldInfo[3].VertIndexes = Amy_LeftLowerArmIndices_DX;
		AmyWeldInfo[3].ModelB = v0;
		AmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftLowerArmIndices_DX) / 2);
		AmyWeldInfo[3].WeldType = 2;
		AmyWeldInfo[3].anonymous_5 = 0;
		AmyWeldInfo[3].VertexBuffer = 0;
		AmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
		AmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
		AmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightKneeIndices_DX) / 2);
		AmyWeldInfo[4].WeldType = 2;
		AmyWeldInfo[4].anonymous_5 = 0;
		AmyWeldInfo[4].VertexBuffer = 0;
		AmyWeldInfo[4].VertIndexes = Amy_RightKneeIndices_DX;
		AmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
		AmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
		AmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightLegIndices_DX) / 2);
		AmyWeldInfo[5].WeldType = 2;
		AmyWeldInfo[5].anonymous_5 = 0;
		AmyWeldInfo[5].VertIndexes = Amy_RightLegIndices_DX;
		AmyWeldInfo[5].VertexBuffer = 0;
		AmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
		v1 = AMY_OBJECTS[16];
		AmyWeldInfo[6].VertIndexes = Amy_LeftKneeIndices_DX;
		AmyWeldInfo[6].ModelB = v1;
		AmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftKneeIndices_DX) / 2);
		AmyWeldInfo[6].WeldType = 2;
		AmyWeldInfo[6].anonymous_5 = 0;
		AmyWeldInfo[6].VertexBuffer = 0;
		AmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
		v2 = AMY_OBJECTS[17];
		AmyWeldInfo[7].VertIndexes = Amy_LeftLegIndices_DX;
		AmyWeldInfo[7].ModelB = v2;
		AmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftLegIndices_DX) / 2);
		AmyWeldInfo[7].WeldType = 2;
		AmyWeldInfo[7].anonymous_5 = 0;
		AmyWeldInfo[7].VertexBuffer = 0;
		AmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
		AmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
		AmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightShoeIndices_DX) / 2);
		AmyWeldInfo[8].WeldType = 2;
		AmyWeldInfo[8].anonymous_5 = 0;
		AmyWeldInfo[8].VertexBuffer = 0;
		AmyWeldInfo[8].VertIndexes = Amy_RightShoeIndices_DX;
		AmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
		v3 = AMY_OBJECTS[21];
		AmyWeldInfo[9].VertIndexes = Amy_LeftShoeIndices_DX;
		AmyWeldInfo[9].ModelB = v3;
		AmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftShoeIndices_DX) / 2);
		AmyWeldInfo[9].WeldType = 2;
		AmyWeldInfo[9].anonymous_5 = 0;
		AmyWeldInfo[9].VertexBuffer = 0;
		AmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
		AmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
		AmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightHandIndices_DX) / 2);
		AmyWeldInfo[10].WeldType = 2;
		AmyWeldInfo[10].anonymous_5 = 0;
		AmyWeldInfo[10].VertexBuffer = 0;
		AmyWeldInfo[10].VertIndexes = Amy_RightHandIndices_DX;
		AmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
		AmyWeldInfo[11].ModelB = AMY_OBJECTS[25];
		AmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftHandIndices_DX) / 2);
		AmyWeldInfo[11].WeldType = 2;
		AmyWeldInfo[11].anonymous_5 = 0;
		AmyWeldInfo[11].VertexBuffer = 0;
		AmyWeldInfo[11].VertIndexes = Amy_LeftHandIndices_DX;
		AmyWeldInfo[12].BaseModel = *AMY_OBJECTS;
		AmyWeldInfo[12].ModelA = AMY_OBJECTS[23];
		AmyWeldInfo[12].ModelB = 0;
		AmyWeldInfo[12].anonymous_5 = 0;
		AmyWeldInfo[12].VertexBuffer = 0;
		AmyWeldInfo[12].VertIndexes = 0;
		AmyWeldInfo[12].WeldType = 4;
		AmyWeldInfo[12].VertexPairCount = 2;
		AmyWeldInfo[13].BaseModel = *AMY_OBJECTS;
		v4 = AMY_OBJECTS[25];
		AmyWeldInfo[13].ModelB = 0;
		AmyWeldInfo[13].anonymous_5 = 0;
		AmyWeldInfo[13].VertexBuffer = 0;
		AmyWeldInfo[13].VertIndexes = 0;
		AmyWeldInfo[13].ModelA = v4;
		AmyWeldInfo[13].VertexPairCount = 2;
		AmyWeldInfo[13].WeldType = 5;
		AmyWeldInfo[14].BaseModel = *AMY_OBJECTS;
		v5 = AMY_OBJECTS[19];
		AmyWeldInfo[14].ModelB = 0;
		AmyWeldInfo[14].VertexPairCount = 0;
		AmyWeldInfo[14].anonymous_5 = 0;
		AmyWeldInfo[14].VertexBuffer = 0;
		AmyWeldInfo[14].VertIndexes = 0;
		AmyWeldInfo[14].ModelA = v5;
		AmyWeldInfo[14].WeldType = 6;
		AmyWeldInfo[15].BaseModel = *AMY_OBJECTS;
		v6 = AMY_OBJECTS[21];
		AmyWeldInfo[15].ModelB = 0;
		AmyWeldInfo[15].VertexPairCount = 0;
		AmyWeldInfo[15].anonymous_5 = 0;
		AmyWeldInfo[15].VertexBuffer = 0;
		AmyWeldInfo[15].VertIndexes = 0;
		AmyWeldInfo[15].ModelA = v6;
		AmyWeldInfo[15].WeldType = 7;
		AmyWeldInfo[16].BaseModel = *AMY_OBJECTS;
		v7 = AMY_OBJECTS[30];
		AmyWeldInfo[16].ModelB = 0;
		AmyWeldInfo[16].VertexPairCount = 0;
		AmyWeldInfo[16].anonymous_5 = 0;
		AmyWeldInfo[16].VertexBuffer = 0;
		AmyWeldInfo[16].VertIndexes = 0;
		AmyWeldInfo[17].BaseModel = 0;
		AmyWeldInfo[17].ModelA = 0;
		AmyWeldInfo[17].ModelB = 0;
		AmyWeldInfo[17].VertexPairCount = 0;
		AmyWeldInfo[17].VertexBuffer = 0;
		AmyWeldInfo[16].ModelA = v7;
		AmyWeldInfo[16].WeldType = 8;
		AmyWeldInfo[17].VertIndexes = 0;
	}

	void __cdecl InitNPCAmyWeldInfo_mod()
	{
		NJS_OBJECT* v0; // edi@1
		NJS_OBJECT* v1; // edi@1
		NJS_OBJECT* v2; // edi@1
		NJS_OBJECT* v3; // edi@1
		NJS_OBJECT* v4; // eax@1

		NPCAmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
		NPCAmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
		NPCAmyWeldInfo[0].anonymous_5 = 0;
		NPCAmyWeldInfo[0].VertexBuffer = 0;
		NPCAmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightUpperArmIndices_DX) / 2);
		NPCAmyWeldInfo[0].WeldType = 2;
		NPCAmyWeldInfo[0].VertIndexes = Amy_RightUpperArmIndices_DX;
		NPCAmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
		NPCAmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
		NPCAmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightLowerArmIndices_DX) / 2);
		NPCAmyWeldInfo[1].WeldType = 2;
		NPCAmyWeldInfo[1].anonymous_5 = 0;
		NPCAmyWeldInfo[1].VertexBuffer = 0;
		NPCAmyWeldInfo[1].VertIndexes = Amy_RightLowerArmIndices_DX;
		NPCAmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
		NPCAmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
		NPCAmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftUpperArmIndices_DX) / 2);
		NPCAmyWeldInfo[2].WeldType = 2;
		NPCAmyWeldInfo[2].anonymous_5 = 0;
		NPCAmyWeldInfo[2].VertexBuffer = 0;
		NPCAmyWeldInfo[2].VertIndexes = Amy_LeftUpperArmIndices_DX;
		NPCAmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
		v0 = AMY_OBJECTS[11];
		NPCAmyWeldInfo[3].VertIndexes = Amy_LeftLowerArmIndices_DX;
		NPCAmyWeldInfo[3].ModelB = v0;
		NPCAmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftLowerArmIndices_DX) / 2);
		NPCAmyWeldInfo[3].WeldType = 2;
		NPCAmyWeldInfo[3].anonymous_5 = 0;
		NPCAmyWeldInfo[3].VertexBuffer = 0;
		NPCAmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
		NPCAmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
		NPCAmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightKneeIndices_DX) / 2);
		NPCAmyWeldInfo[4].WeldType = 2;
		NPCAmyWeldInfo[4].anonymous_5 = 0;
		NPCAmyWeldInfo[4].VertexBuffer = 0;
		NPCAmyWeldInfo[4].VertIndexes = Amy_RightKneeIndices_DX;
		NPCAmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
		NPCAmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
		NPCAmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightLegIndices_DX) / 2);
		NPCAmyWeldInfo[5].WeldType = 2;
		NPCAmyWeldInfo[5].anonymous_5 = 0;
		NPCAmyWeldInfo[5].VertexBuffer = 0;
		NPCAmyWeldInfo[5].VertIndexes = Amy_RightLegIndices_DX;
		NPCAmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
		v1 = AMY_OBJECTS[16];
		NPCAmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftKneeIndices_DX) / 2);
		NPCAmyWeldInfo[6].anonymous_5 = 0;
		NPCAmyWeldInfo[6].VertexBuffer = 0;
		NPCAmyWeldInfo[6].VertIndexes = Amy_LeftKneeIndices_DX;
		NPCAmyWeldInfo[6].ModelB = v1;
		NPCAmyWeldInfo[6].WeldType = 2;
		NPCAmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
		v2 = AMY_OBJECTS[17];
		NPCAmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftLegIndices_DX) / 2);
		NPCAmyWeldInfo[7].anonymous_5 = 0;
		NPCAmyWeldInfo[7].VertexBuffer = 0;
		NPCAmyWeldInfo[7].VertIndexes = Amy_LeftLegIndices_DX;
		NPCAmyWeldInfo[7].ModelB = v2;
		NPCAmyWeldInfo[7].WeldType = 2;
		NPCAmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
		NPCAmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
		NPCAmyWeldInfo[8].anonymous_5 = 0;
		NPCAmyWeldInfo[8].VertexBuffer = 0;
		NPCAmyWeldInfo[8].WeldType = 2;
		NPCAmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightShoeIndices_DX) / 2);
		NPCAmyWeldInfo[8].VertIndexes = Amy_RightShoeIndices_DX;
		NPCAmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
		v3 = AMY_OBJECTS[21];
		NPCAmyWeldInfo[9].anonymous_5 = 0;
		NPCAmyWeldInfo[9].VertexBuffer = 0;
		NPCAmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftShoeIndices_DX) / 2);
		NPCAmyWeldInfo[9].VertIndexes = Amy_LeftShoeIndices_DX;
		NPCAmyWeldInfo[9].ModelB = v3;
		NPCAmyWeldInfo[9].WeldType = 2;
		NPCAmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
		NPCAmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
		NPCAmyWeldInfo[10].anonymous_5 = 0;
		NPCAmyWeldInfo[10].VertexBuffer = 0;
		NPCAmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_RightHandIndices_DX) / 2);
		NPCAmyWeldInfo[10].WeldType = 2;
		NPCAmyWeldInfo[10].VertIndexes = Amy_RightHandIndices_DX;
		NPCAmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
		NPCAmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
		v4 = AMY_OBJECTS[25];
		NPCAmyWeldInfo[11].anonymous_5 = 0;
		NPCAmyWeldInfo[11].VertexBuffer = 0;
		NPCAmyWeldInfo[12].BaseModel = 0;
		NPCAmyWeldInfo[12].ModelA = 0;
		NPCAmyWeldInfo[11].ModelB = v4;
		NPCAmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LeftHandIndices_DX) / 2);
		NPCAmyWeldInfo[11].WeldType = 2;
		NPCAmyWeldInfo[11].VertIndexes = Amy_LeftHandIndices_DX;
		NPCAmyWeldInfo[12].ModelB = 0;
		NPCAmyWeldInfo[12].VertexPairCount = 0;
		NPCAmyWeldInfo[12].VertexBuffer = 0;
		NPCAmyWeldInfo[12].VertIndexes = 0;
	}

	uint16_t Tails_RightUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Tails_RightLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Tails_LeftUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Tails_LeftLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Tails_RightKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Tails_RightLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Tails_LeftKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Tails_LeftLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Tails_RightHandIndices_DX[] = {
		8, 56,
		37, 388,
		38, 387,
		39, 386,
		0, 0,
		46, 412,
		47, 411,
		48, 410,
		11, 55,
		67, 577,
		68, 576,
		69, 575,
		1, 1,
		61, 427,
		62, 426,
		63, 425,
		5, 3,
		52, 106,
		53, 105,
		54, 104,
		9, 54,
		16, 535,
		17, 534,
		18, 533,
		4, 2,
		28, 556,
		29, 555,
		30, 554,
	};

	uint16_t Tails_LeftHandIndices_DX[] = {
		8, 56,
		61, 598,
		62, 597,
		63, 596,
		4, 2,
		67, 589,
		68, 588,
		69, 587,
		9, 54,
		22, 73,
		23, 72,
		24, 71,
		5, 3,
		31, 136,
		32, 435,
		33, 434,
		1, 1,
		34, 565,
		35, 564,
		36, 563,
		11, 55,
		40, 472,
		41, 471,
		42, 470,
		0, 0,
		49, 445,
		50, 444,
		51, 443,
	};

	uint16_t Tails_RightShoeIndices_DX[] = {
		63, 85,
		153, 164,
		174, 147,
		176, 146,
		213, 177,
		212, 178,
		183, 144,
		182, 145,
		203, 163,
		93, 31,
		94, 90,
		36, 80,
		35, 79,
		41, 78,
		42, 77,
		143, 76,
		144, 75,
		147, 74,
		150, 73,
		151, 71,
		57, 72,
		58, 83,
		24, 82,
		26, 81,
		61, 84,
	};

	uint16_t Tails_LeftShoeIndices_DX[] = {
		63, 86,
		150, 164,
		171, 147,
		172, 146,
		211, 177,
		209, 178,
		180, 144,
		179, 145,
		200, 163,
		93, 91,
		94, 89,
		37, 80,
		35, 79,
		41, 78,
		42, 77,
		140, 76,
		141, 75,
		144, 74,
		147, 73,
		148, 71,
		57, 72,
		58, 83,
		24, 82,
		25, 81,
		61, 84,
	};

	void __cdecl InitTailsWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // edx@1
		NJS_OBJECT* v4; // edx@1
		NJS_OBJECT* v5; // eax@1

		TailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
		TailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
		TailsWeldInfo[0].anonymous_5 = 0;
		TailsWeldInfo[0].VertexBuffer = 0;
		TailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightUpperArmIndices_DX) / 2);
		TailsWeldInfo[0].WeldType = 2;
		TailsWeldInfo[0].VertIndexes = Tails_RightUpperArmIndices_DX;
		TailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
		TailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
		TailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLowerArmIndices_DX) / 2);
		TailsWeldInfo[1].WeldType = 2;
		TailsWeldInfo[1].anonymous_5 = 0;
		TailsWeldInfo[1].VertexBuffer = 0;
		TailsWeldInfo[1].VertIndexes = Tails_RightLowerArmIndices_DX;
		TailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
		v0 = MILES_OBJECTS[24];
		TailsWeldInfo[2].VertIndexes = Tails_LeftUpperArmIndices_DX;
		TailsWeldInfo[2].ModelB = v0;
		TailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftUpperArmIndices_DX) / 2);
		TailsWeldInfo[2].WeldType = 2;
		TailsWeldInfo[2].anonymous_5 = 0;
		TailsWeldInfo[2].VertexBuffer = 0;
		TailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
		TailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
		TailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLowerArmIndices_DX) / 2);
		TailsWeldInfo[3].WeldType = 2;
		TailsWeldInfo[3].anonymous_5 = 0;
		TailsWeldInfo[3].VertexBuffer = 0;
		TailsWeldInfo[3].VertIndexes = Tails_LeftLowerArmIndices_DX;
		TailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
		TailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
		TailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightKneeIndices_DX) / 2);
		TailsWeldInfo[4].WeldType = 2;
		TailsWeldInfo[4].anonymous_5 = 0;
		TailsWeldInfo[4].VertexBuffer = 0;
		TailsWeldInfo[4].VertIndexes = Tails_RightKneeIndices_DX;
		TailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
		TailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
		TailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLegIndices_DX) / 2);
		TailsWeldInfo[5].WeldType = 2;
		TailsWeldInfo[5].anonymous_5 = 0;
		TailsWeldInfo[5].VertexBuffer = 0;
		TailsWeldInfo[5].VertIndexes = Tails_RightLegIndices_DX;
		TailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
		TailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
		TailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftKneeIndices_DX) / 2);
		TailsWeldInfo[6].WeldType = 2;
		TailsWeldInfo[6].anonymous_5 = 0;
		TailsWeldInfo[6].VertexBuffer = 0;
		TailsWeldInfo[6].VertIndexes = Tails_LeftKneeIndices_DX;
		TailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
		TailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
		TailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLegIndices_DX) / 2);
		TailsWeldInfo[7].WeldType = 2;
		TailsWeldInfo[7].anonymous_5 = 0;
		TailsWeldInfo[7].VertexBuffer = 0;
		TailsWeldInfo[7].VertIndexes = Tails_LeftLegIndices_DX;
		TailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
		TailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
		TailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightShoeIndices_DX) / 2);
		TailsWeldInfo[8].WeldType = 2;
		TailsWeldInfo[8].anonymous_5 = 0;
		TailsWeldInfo[8].VertexBuffer = 0;
		TailsWeldInfo[8].VertIndexes = Tails_RightShoeIndices_DX;
		TailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
		v1 = MILES_OBJECTS[35];
		TailsWeldInfo[9].VertIndexes = Tails_LeftShoeIndices_DX;
		TailsWeldInfo[9].ModelB = v1;
		TailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftShoeIndices_DX) / 2);
		TailsWeldInfo[9].WeldType = 2;
		TailsWeldInfo[9].anonymous_5 = 0;
		TailsWeldInfo[9].VertexBuffer = 0;
		TailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
		TailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
		TailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightHandIndices_DX) / 2);
		TailsWeldInfo[10].WeldType = 2;
		TailsWeldInfo[10].anonymous_5 = 0;
		TailsWeldInfo[10].VertexBuffer = 0;
		TailsWeldInfo[10].VertIndexes = Tails_RightHandIndices_DX;
		TailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
		TailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
		TailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftHandIndices_DX) / 2);
		TailsWeldInfo[11].WeldType = 2;
		TailsWeldInfo[11].anonymous_5 = 0;
		TailsWeldInfo[11].VertexBuffer = 0;
		TailsWeldInfo[11].VertIndexes = Tails_LeftHandIndices_DX;
		TailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
		TailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
		TailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightUpperArmIndices_DX) / 2);
		TailsWeldInfo[12].WeldType = 2;
		TailsWeldInfo[12].anonymous_5 = 0;
		TailsWeldInfo[12].VertexBuffer = 0;
		TailsWeldInfo[12].VertIndexes = Tails_RightUpperArmIndices_DX;
		TailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
		TailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
		TailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLowerArmIndices_DX) / 2);
		TailsWeldInfo[13].WeldType = 2;
		TailsWeldInfo[13].anonymous_5 = 0;
		TailsWeldInfo[13].VertexBuffer = 0;
		TailsWeldInfo[13].VertIndexes = Tails_RightLowerArmIndices_DX;
		TailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
		TailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
		TailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftUpperArmIndices_DX) / 2);
		TailsWeldInfo[14].WeldType = 2;
		TailsWeldInfo[14].anonymous_5 = 0;
		TailsWeldInfo[14].VertexBuffer = 0;
		TailsWeldInfo[14].VertIndexes = Tails_LeftUpperArmIndices_DX;
		TailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
		TailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
		TailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLowerArmIndices_DX) / 2);
		TailsWeldInfo[15].WeldType = 2;
		TailsWeldInfo[15].anonymous_5 = 0;
		TailsWeldInfo[15].VertexBuffer = 0;
		TailsWeldInfo[15].VertIndexes = Tails_LeftLowerArmIndices_DX;
		TailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
		TailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
		TailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightKneeIndices_DX) / 2);
		TailsWeldInfo[16].WeldType = 2;
		TailsWeldInfo[16].anonymous_5 = 0;
		TailsWeldInfo[16].VertexBuffer = 0;
		TailsWeldInfo[16].VertIndexes = Tails_RightKneeIndices_DX;
		TailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
		TailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
		TailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLegIndices_DX) / 2);
		TailsWeldInfo[17].WeldType = 2;
		TailsWeldInfo[17].anonymous_5 = 0;
		TailsWeldInfo[17].VertexBuffer = 0;
		TailsWeldInfo[17].VertIndexes = Tails_RightLegIndices_DX;
		TailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
		TailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
		TailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftKneeIndices_DX) / 2);
		TailsWeldInfo[18].WeldType = 2;
		TailsWeldInfo[18].anonymous_5 = 0;
		TailsWeldInfo[18].VertexBuffer = 0;
		TailsWeldInfo[18].VertIndexes = Tails_LeftKneeIndices_DX;
		TailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
		v2 = MILES_OBJECTS[51];
		TailsWeldInfo[19].VertIndexes = Tails_LeftLegIndices_DX;
		TailsWeldInfo[19].ModelB = v2;
		TailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLegIndices_DX) / 2);
		TailsWeldInfo[19].WeldType = 2;
		TailsWeldInfo[19].anonymous_5 = 0;
		TailsWeldInfo[19].VertexBuffer = 0;
		TailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
		TailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
		TailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightShoeIndices_DX) / 2);
		TailsWeldInfo[20].WeldType = 2;
		TailsWeldInfo[20].anonymous_5 = 0;
		TailsWeldInfo[20].VertexBuffer = 0;
		TailsWeldInfo[20].VertIndexes = Tails_RightShoeIndices_DX;
		TailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
		TailsWeldInfo[21].ModelB = MILES_OBJECTS[55];
		TailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftShoeIndices_DX) / 2);
		TailsWeldInfo[21].WeldType = 2;
		TailsWeldInfo[21].anonymous_5 = 0;
		TailsWeldInfo[21].VertexBuffer = 0;
		TailsWeldInfo[21].VertIndexes = Tails_LeftShoeIndices_DX;
		TailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
		TailsWeldInfo[22].ModelB = MILES_OBJECTS[57];
		TailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightHandIndices_DX) / 2);
		TailsWeldInfo[22].WeldType = 2;
		TailsWeldInfo[22].anonymous_5 = 0;
		TailsWeldInfo[22].VertexBuffer = 0;
		TailsWeldInfo[22].VertIndexes = Tails_RightHandIndices_DX;
		TailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
		TailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
		TailsWeldInfo[23].ModelB = MILES_OBJECTS[59];
		TailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftHandIndices_DX) / 2);
		TailsWeldInfo[23].WeldType = 2;
		TailsWeldInfo[23].anonymous_5 = 0;
		TailsWeldInfo[23].VertexBuffer = 0;
		TailsWeldInfo[23].VertIndexes = Tails_LeftHandIndices_DX;
		TailsWeldInfo[24].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[24].ModelA = MILES_OBJECTS[37];
		TailsWeldInfo[24].ModelB = 0;
		TailsWeldInfo[24].VertexPairCount = 2;
		TailsWeldInfo[24].WeldType = 4;
		TailsWeldInfo[24].anonymous_5 = 0;
		TailsWeldInfo[24].VertexBuffer = 0;
		TailsWeldInfo[24].VertIndexes = 0;
		TailsWeldInfo[25].BaseModel = *MILES_OBJECTS;
		TailsWeldInfo[25].ModelA = MILES_OBJECTS[39];
		TailsWeldInfo[25].ModelB = 0;
		TailsWeldInfo[25].VertexPairCount = 2;
		TailsWeldInfo[25].WeldType = 5;
		TailsWeldInfo[25].anonymous_5 = 0;
		TailsWeldInfo[25].VertexBuffer = 0;
		TailsWeldInfo[25].VertIndexes = 0;
		TailsWeldInfo[26].BaseModel = *MILES_OBJECTS;
		v3 = MILES_OBJECTS[33];
		TailsWeldInfo[26].ModelB = 0;
		TailsWeldInfo[26].VertexPairCount = 0;
		TailsWeldInfo[26].anonymous_5 = 0;
		TailsWeldInfo[26].VertexBuffer = 0;
		TailsWeldInfo[26].VertIndexes = 0;
		TailsWeldInfo[26].ModelA = v3;
		TailsWeldInfo[26].WeldType = 6;
		TailsWeldInfo[27].BaseModel = *MILES_OBJECTS;
		v4 = MILES_OBJECTS[35];
		TailsWeldInfo[27].ModelB = 0;
		TailsWeldInfo[27].VertexPairCount = 0;
		TailsWeldInfo[27].anonymous_5 = 0;
		TailsWeldInfo[27].VertexBuffer = 0;
		TailsWeldInfo[27].VertIndexes = 0;
		TailsWeldInfo[27].ModelA = v4;
		TailsWeldInfo[27].WeldType = 7;
		TailsWeldInfo[28].BaseModel = *MILES_OBJECTS;
		v5 = MILES_OBJECTS[4];
		TailsWeldInfo[28].ModelB = 0;
		TailsWeldInfo[28].VertexPairCount = 0;
		TailsWeldInfo[28].anonymous_5 = 0;
		TailsWeldInfo[28].VertexBuffer = 0;
		TailsWeldInfo[28].VertIndexes = 0;
		TailsWeldInfo[29].BaseModel = 0;
		TailsWeldInfo[29].ModelA = 0;
		TailsWeldInfo[29].ModelB = 0;
		TailsWeldInfo[29].VertexPairCount = 0;
		TailsWeldInfo[29].VertexBuffer = 0;
		TailsWeldInfo[28].ModelA = v5;
		TailsWeldInfo[28].WeldType = 8;
		TailsWeldInfo[29].VertIndexes = 0;
	}

	void __cdecl InitNPCTailsWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebx@1
		NJS_OBJECT* v4; // esi@1
		NJS_OBJECT* v5; // eax@1

		NPCTailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
		NPCTailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
		NPCTailsWeldInfo[0].anonymous_5 = 0;
		NPCTailsWeldInfo[0].VertexBuffer = 0;
		NPCTailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightUpperArmIndices_DX) / 2);
		NPCTailsWeldInfo[0].WeldType = 2;
		NPCTailsWeldInfo[0].VertIndexes = Tails_RightUpperArmIndices_DX;
		NPCTailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
		NPCTailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
		NPCTailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLowerArmIndices_DX) / 2);
		NPCTailsWeldInfo[1].WeldType = 2;
		NPCTailsWeldInfo[1].anonymous_5 = 0;
		NPCTailsWeldInfo[1].VertexBuffer = 0;
		NPCTailsWeldInfo[1].VertIndexes = Tails_RightLowerArmIndices_DX;
		NPCTailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
		v0 = MILES_OBJECTS[24];
		NPCTailsWeldInfo[2].VertIndexes = Tails_LeftUpperArmIndices_DX;
		NPCTailsWeldInfo[2].ModelB = v0;
		NPCTailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftUpperArmIndices_DX) / 2);
		NPCTailsWeldInfo[2].WeldType = 2;
		NPCTailsWeldInfo[2].anonymous_5 = 0;
		NPCTailsWeldInfo[2].VertexBuffer = 0;
		NPCTailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
		NPCTailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
		NPCTailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLowerArmIndices_DX) / 2);
		NPCTailsWeldInfo[3].WeldType = 2;
		NPCTailsWeldInfo[3].anonymous_5 = 0;
		NPCTailsWeldInfo[3].VertexBuffer = 0;
		NPCTailsWeldInfo[3].VertIndexes = Tails_LeftLowerArmIndices_DX;
		NPCTailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
		NPCTailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
		NPCTailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightKneeIndices_DX) / 2);
		NPCTailsWeldInfo[4].WeldType = 2;
		NPCTailsWeldInfo[4].anonymous_5 = 0;
		NPCTailsWeldInfo[4].VertexBuffer = 0;
		NPCTailsWeldInfo[4].VertIndexes = Tails_RightKneeIndices_DX;
		NPCTailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
		NPCTailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
		NPCTailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLegIndices_DX) / 2);
		NPCTailsWeldInfo[5].WeldType = 2;
		NPCTailsWeldInfo[5].anonymous_5 = 0;
		NPCTailsWeldInfo[5].VertexBuffer = 0;
		NPCTailsWeldInfo[5].VertIndexes = Tails_RightLegIndices_DX;
		NPCTailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
		NPCTailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
		NPCTailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftKneeIndices_DX) / 2);
		NPCTailsWeldInfo[6].WeldType = 2;
		NPCTailsWeldInfo[6].anonymous_5 = 0;
		NPCTailsWeldInfo[6].VertexBuffer = 0;
		NPCTailsWeldInfo[6].VertIndexes = Tails_LeftKneeIndices_DX;
		NPCTailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
		NPCTailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
		NPCTailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLegIndices_DX) / 2);
		NPCTailsWeldInfo[7].WeldType = 2;
		NPCTailsWeldInfo[7].anonymous_5 = 0;
		NPCTailsWeldInfo[7].VertexBuffer = 0;
		NPCTailsWeldInfo[7].VertIndexes = Tails_LeftLegIndices_DX;
		NPCTailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
		NPCTailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
		NPCTailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightShoeIndices_DX) / 2);
		NPCTailsWeldInfo[8].WeldType = 2;
		NPCTailsWeldInfo[8].anonymous_5 = 0;
		NPCTailsWeldInfo[8].VertexBuffer = 0;
		NPCTailsWeldInfo[8].VertIndexes = Tails_RightShoeIndices_DX;
		NPCTailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
		v1 = MILES_OBJECTS[35];
		NPCTailsWeldInfo[9].VertIndexes = Tails_LeftShoeIndices_DX;
		NPCTailsWeldInfo[9].ModelB = v1;
		NPCTailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftShoeIndices_DX) / 2);
		NPCTailsWeldInfo[9].WeldType = 2;
		NPCTailsWeldInfo[9].anonymous_5 = 0;
		NPCTailsWeldInfo[9].VertexBuffer = 0;
		NPCTailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
		NPCTailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
		NPCTailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightHandIndices_DX) / 2);
		NPCTailsWeldInfo[10].WeldType = 2;
		NPCTailsWeldInfo[10].anonymous_5 = 0;
		NPCTailsWeldInfo[10].VertexBuffer = 0;
		NPCTailsWeldInfo[10].VertIndexes = Tails_RightHandIndices_DX;
		NPCTailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
		NPCTailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
		NPCTailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
		NPCTailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftHandIndices_DX) / 2);
		NPCTailsWeldInfo[11].WeldType = 2;
		NPCTailsWeldInfo[11].anonymous_5 = 0;
		NPCTailsWeldInfo[11].VertexBuffer = 0;
		NPCTailsWeldInfo[11].VertIndexes = Tails_LeftHandIndices_DX;
		NPCTailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
		NPCTailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
		NPCTailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightUpperArmIndices_DX) / 2);
		NPCTailsWeldInfo[12].WeldType = 2;
		NPCTailsWeldInfo[12].anonymous_5 = 0;
		NPCTailsWeldInfo[12].VertexBuffer = 0;
		NPCTailsWeldInfo[12].VertIndexes = Tails_RightUpperArmIndices_DX;
		NPCTailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
		NPCTailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
		NPCTailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLowerArmIndices_DX) / 2);
		NPCTailsWeldInfo[13].WeldType = 2;
		NPCTailsWeldInfo[13].anonymous_5 = 0;
		NPCTailsWeldInfo[13].VertexBuffer = 0;
		NPCTailsWeldInfo[13].VertIndexes = Tails_RightLowerArmIndices_DX;
		NPCTailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
		NPCTailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
		NPCTailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftUpperArmIndices_DX) / 2);
		NPCTailsWeldInfo[14].WeldType = 2;
		NPCTailsWeldInfo[14].anonymous_5 = 0;
		NPCTailsWeldInfo[14].VertexBuffer = 0;
		NPCTailsWeldInfo[14].VertIndexes = Tails_LeftUpperArmIndices_DX;
		NPCTailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
		NPCTailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
		NPCTailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLowerArmIndices_DX) / 2);
		NPCTailsWeldInfo[15].WeldType = 2;
		NPCTailsWeldInfo[15].anonymous_5 = 0;
		NPCTailsWeldInfo[15].VertexBuffer = 0;
		NPCTailsWeldInfo[15].VertIndexes = Tails_LeftLowerArmIndices_DX;
		NPCTailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
		NPCTailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
		NPCTailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightKneeIndices_DX) / 2);
		NPCTailsWeldInfo[16].WeldType = 2;
		NPCTailsWeldInfo[16].anonymous_5 = 0;
		NPCTailsWeldInfo[16].VertexBuffer = 0;
		NPCTailsWeldInfo[16].VertIndexes = Tails_RightKneeIndices_DX;
		NPCTailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
		NPCTailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
		NPCTailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightLegIndices_DX) / 2);
		NPCTailsWeldInfo[17].WeldType = 2;
		NPCTailsWeldInfo[17].anonymous_5 = 0;
		NPCTailsWeldInfo[17].VertexBuffer = 0;
		NPCTailsWeldInfo[17].VertIndexes = Tails_RightLegIndices_DX;
		NPCTailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
		NPCTailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
		NPCTailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftKneeIndices_DX) / 2);
		NPCTailsWeldInfo[18].WeldType = 2;
		NPCTailsWeldInfo[18].anonymous_5 = 0;
		NPCTailsWeldInfo[18].VertexBuffer = 0;
		NPCTailsWeldInfo[18].VertIndexes = Tails_LeftKneeIndices_DX;
		NPCTailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
		v2 = MILES_OBJECTS[51];
		NPCTailsWeldInfo[19].anonymous_5 = 0;
		NPCTailsWeldInfo[19].VertexBuffer = 0;
		NPCTailsWeldInfo[19].VertIndexes = Tails_LeftLegIndices_DX;
		NPCTailsWeldInfo[19].ModelB = v2;
		NPCTailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftLegIndices_DX) / 2);
		NPCTailsWeldInfo[19].WeldType = 2;
		NPCTailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
		NPCTailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
		NPCTailsWeldInfo[20].anonymous_5 = 0;
		NPCTailsWeldInfo[20].VertexBuffer = 0;
		NPCTailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightShoeIndices_DX) / 2);
		NPCTailsWeldInfo[20].WeldType = 2;
		NPCTailsWeldInfo[20].VertIndexes = Tails_RightShoeIndices_DX;
		NPCTailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
		v3 = MILES_OBJECTS[55];
		NPCTailsWeldInfo[21].anonymous_5 = 0;
		NPCTailsWeldInfo[21].VertexBuffer = 0;
		NPCTailsWeldInfo[21].ModelB = v3;
		NPCTailsWeldInfo[21].VertIndexes = Tails_LeftShoeIndices_DX;
		NPCTailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftShoeIndices_DX) / 2);
		NPCTailsWeldInfo[21].WeldType = 2;
		NPCTailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
		v4 = MILES_OBJECTS[57];
		NPCTailsWeldInfo[22].anonymous_5 = 0;
		NPCTailsWeldInfo[22].VertexBuffer = 0;
		NPCTailsWeldInfo[22].ModelB = v4;
		NPCTailsWeldInfo[22].VertIndexes = Tails_RightHandIndices_DX;
		NPCTailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_RightHandIndices_DX) / 2);
		NPCTailsWeldInfo[22].WeldType = 2;
		NPCTailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
		NPCTailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
		v5 = MILES_OBJECTS[59];
		NPCTailsWeldInfo[23].anonymous_5 = 0;
		NPCTailsWeldInfo[23].VertexBuffer = 0;
		NPCTailsWeldInfo[24].BaseModel = 0;
		NPCTailsWeldInfo[24].ModelA = 0;
		NPCTailsWeldInfo[23].VertIndexes = Tails_LeftHandIndices_DX;
		NPCTailsWeldInfo[24].ModelB = 0;
		NPCTailsWeldInfo[24].VertexPairCount = 0;
		NPCTailsWeldInfo[24].VertexBuffer = 0;
		NPCTailsWeldInfo[23].ModelB = v5;
		NPCTailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LeftHandIndices_DX) / 2);
		NPCTailsWeldInfo[23].WeldType = 2;
		NPCTailsWeldInfo[24].VertIndexes = 0;
	}

	uint16_t Knuckles_RightUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Knuckles_RightLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Knuckles_LeftUpperArmIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Knuckles_LeftLowerArmIndices_DX[] = {
		4, 6,
		5, 7,
		1, 3,
		0, 2,
	};

	uint16_t Knuckles_RightKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Knuckles_RightLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Knuckles_LeftKneeIndices_DX[] = {
		0, 2,
		4, 6,
		5, 7,
		1, 3,
	};

	uint16_t Knuckles_LeftLegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Knuckles_RightHandIndices_DX[] = {
		8, 24,
		103, 236,
		104, 235,
		105, 234,
		0, 11,
		97, 140,
		98, 139,
		99, 138,
		19, 42,
		88, 305,
		89, 304,
		90, 303,
		1, 13,
		79, 167,
		80, 166,
		81, 165,
		17, 17,
		70, 317,
		71, 316,
		72, 315,
		5, 15,
		121, 278,
		122, 277,
		123, 276,
		18, 41,
		34, 269,
		35, 268,
		36, 267,
		4, 10,
		40, 230,
		41, 229,
		42, 228,
	};

	uint16_t Knuckles_LeftHandIndices_DX[] = {
		8, 24,
		40, 233,
		41, 232,
		42, 231,
		4, 10,
		37, 284,
		38, 283,
		39, 282,
		18, 41,
		124, 287,
		125, 286,
		126, 285,
		5, 15,
		73, 278,
		74, 277,
		75, 276,
		17, 17,
		82, 170,
		83, 169,
		84, 168,
		1, 13,
		91, 317,
		92, 316,
		93, 315,
		19, 42,
		100, 140,
		101, 139,
		102, 138,
		0, 11,
		103, 236,
		104, 235,
		105, 234,
	};

	uint16_t Knuckles_RightShoeIndices_DX[] = {
		207, 95,
		206, 93,
		22, 103,
		262, 140,
		246, 139,
		244, 138,
		288, 174,
		300, 175,
		270, 147,
		213, 99,
		215, 100,
		178, 81,
		179, 87,
		180, 86,
		181, 88,
		182, 89,
		54, 90,
		615, 91,
		606, 9,
		605, 11,
		595, 82,
		489, 44,
		487, 43,
		504, 5,
		505, 3,
		514, 53,
		50, 52,
		112, 51,
		111, 50,
		110, 48,
		109, 49,
		108, 45,
	};

	uint16_t Knuckles_LeftShoeIndices_DX[] = {
		208, 94,
		206, 93,
		222, 103,
		262, 140,
		246, 139,
		288, 174,
		300, 175,
		270, 147,
		213, 99,
		214, 101,
		178, 83,
		179, 87,
		180, 86,
		181, 88,
		182, 89,
		55, 90,
		615, 91,
		606, 9,
		605, 11,
		595, 82,
		489, 44,
		488, 43,
		504, 5,
		505, 3,
		514, 53,
		50, 52,
		112, 51,
		111, 50,
		110, 48,
		109, 49,
		108, 46,
	};

	void __cdecl InitKnucklesWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // edx@1
		NJS_OBJECT* v4; // edx@1
		NJS_OBJECT* v5; // eax@1

		KnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
		KnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
		KnucklesWeldInfo[0].anonymous_5 = 0;
		KnucklesWeldInfo[0].VertexBuffer = 0;
		KnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightUpperArmIndices_DX) / 2);
		KnucklesWeldInfo[0].WeldType = 2;
		KnucklesWeldInfo[0].VertIndexes = Knuckles_RightUpperArmIndices_DX;
		KnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
		KnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
		KnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLowerArmIndices_DX) / 2);
		KnucklesWeldInfo[1].WeldType = 2;
		KnucklesWeldInfo[1].anonymous_5 = 0;
		KnucklesWeldInfo[1].VertexBuffer = 0;
		KnucklesWeldInfo[1].VertIndexes = Knuckles_RightLowerArmIndices_DX;
		KnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
		v0 = KNUCKLES_OBJECTS[7];
		KnucklesWeldInfo[2].VertIndexes = Knuckles_LeftUpperArmIndices_DX;
		KnucklesWeldInfo[2].ModelB = v0;
		KnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftUpperArmIndices_DX) / 2);
		KnucklesWeldInfo[2].WeldType = 2;
		KnucklesWeldInfo[2].anonymous_5 = 0;
		KnucklesWeldInfo[2].VertexBuffer = 0;
		KnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
		KnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
		KnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLowerArmIndices_DX) / 2);
		KnucklesWeldInfo[3].WeldType = 2;
		KnucklesWeldInfo[3].anonymous_5 = 0;
		KnucklesWeldInfo[3].VertexBuffer = 0;
		KnucklesWeldInfo[3].VertIndexes = Knuckles_LeftLowerArmIndices_DX;
		KnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
		KnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
		KnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightKneeIndices_DX) / 2);
		KnucklesWeldInfo[4].WeldType = 2;
		KnucklesWeldInfo[4].anonymous_5 = 0;
		KnucklesWeldInfo[4].VertexBuffer = 0;
		KnucklesWeldInfo[4].VertIndexes = Knuckles_RightKneeIndices_DX;
		KnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
		KnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
		KnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLegIndices_DX) / 2);
		KnucklesWeldInfo[5].WeldType = 2;
		KnucklesWeldInfo[5].anonymous_5 = 0;
		KnucklesWeldInfo[5].VertexBuffer = 0;
		KnucklesWeldInfo[5].VertIndexes = Knuckles_RightLegIndices_DX;
		KnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
		KnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
		KnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftKneeIndices_DX) / 2);
		KnucklesWeldInfo[6].WeldType = 2;
		KnucklesWeldInfo[6].anonymous_5 = 0;
		KnucklesWeldInfo[6].VertexBuffer = 0;
		KnucklesWeldInfo[6].VertIndexes = Knuckles_LeftKneeIndices_DX;
		KnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
		KnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
		KnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLegIndices_DX) / 2);
		KnucklesWeldInfo[7].WeldType = 2;
		KnucklesWeldInfo[7].anonymous_5 = 0;
		KnucklesWeldInfo[7].VertexBuffer = 0;
		KnucklesWeldInfo[7].VertIndexes = Knuckles_LeftLegIndices_DX;
		KnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
		KnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
		KnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightShoeIndices_DX) / 2);
		KnucklesWeldInfo[8].WeldType = 2;
		KnucklesWeldInfo[8].anonymous_5 = 0;
		KnucklesWeldInfo[8].VertexBuffer = 0;
		KnucklesWeldInfo[8].VertIndexes = Knuckles_RightShoeIndices_DX;
		KnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
		v1 = KNUCKLES_OBJECTS[19];
		KnucklesWeldInfo[9].VertIndexes = Knuckles_LeftShoeIndices_DX;
		KnucklesWeldInfo[9].ModelB = v1;
		KnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftShoeIndices_DX) / 2);
		KnucklesWeldInfo[9].WeldType = 2;
		KnucklesWeldInfo[9].anonymous_5 = 0;
		KnucklesWeldInfo[9].VertexBuffer = 0;

		KnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
		KnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
		KnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightUpperArmIndices_DX) / 2);
		KnucklesWeldInfo[12].WeldType = 2;
		KnucklesWeldInfo[12].anonymous_5 = 0;
		KnucklesWeldInfo[12].VertexBuffer = 0;
		KnucklesWeldInfo[12].VertIndexes = Knuckles_RightUpperArmIndices_DX;
		KnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
		KnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
		KnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLowerArmIndices_DX) / 2);
		KnucklesWeldInfo[13].WeldType = 2;
		KnucklesWeldInfo[13].anonymous_5 = 0;
		KnucklesWeldInfo[13].VertexBuffer = 0;
		KnucklesWeldInfo[13].VertIndexes = Knuckles_RightLowerArmIndices_DX;
		KnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
		KnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
		KnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftUpperArmIndices_DX) / 2);
		KnucklesWeldInfo[14].WeldType = 2;
		KnucklesWeldInfo[14].anonymous_5 = 0;
		KnucklesWeldInfo[14].VertexBuffer = 0;
		KnucklesWeldInfo[14].VertIndexes = Knuckles_LeftUpperArmIndices_DX;
		KnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
		KnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
		KnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLowerArmIndices_DX) / 2);
		KnucklesWeldInfo[15].WeldType = 2;
		KnucklesWeldInfo[15].anonymous_5 = 0;
		KnucklesWeldInfo[15].VertexBuffer = 0;
		KnucklesWeldInfo[15].VertIndexes = Knuckles_LeftLowerArmIndices_DX;
		KnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
		KnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
		KnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightKneeIndices_DX) / 2);
		KnucklesWeldInfo[16].WeldType = 2;
		KnucklesWeldInfo[16].anonymous_5 = 0;
		KnucklesWeldInfo[16].VertexBuffer = 0;
		KnucklesWeldInfo[16].VertIndexes = Knuckles_RightKneeIndices_DX;
		KnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
		KnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
		KnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLegIndices_DX) / 2);
		KnucklesWeldInfo[17].WeldType = 2;
		KnucklesWeldInfo[17].anonymous_5 = 0;
		KnucklesWeldInfo[17].VertexBuffer = 0;
		KnucklesWeldInfo[17].VertIndexes = Knuckles_RightLegIndices_DX;
		KnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
		KnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
		KnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftKneeIndices_DX) / 2);
		KnucklesWeldInfo[18].WeldType = 2;
		KnucklesWeldInfo[18].anonymous_5 = 0;
		KnucklesWeldInfo[18].VertexBuffer = 0;
		KnucklesWeldInfo[18].VertIndexes = Knuckles_LeftKneeIndices_DX;
		KnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
		v2 = KNUCKLES_OBJECTS[37];
		KnucklesWeldInfo[19].VertIndexes = Knuckles_LeftLegIndices_DX;
		KnucklesWeldInfo[19].ModelB = v2;
		KnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLegIndices_DX) / 2);
		KnucklesWeldInfo[19].WeldType = 2;
		KnucklesWeldInfo[19].anonymous_5 = 0;
		KnucklesWeldInfo[19].VertexBuffer = 0;
		KnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
		KnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
		KnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightShoeIndices_DX) / 2);
		KnucklesWeldInfo[20].WeldType = 2;
		KnucklesWeldInfo[20].anonymous_5 = 0;
		KnucklesWeldInfo[20].VertexBuffer = 0;
		KnucklesWeldInfo[20].VertIndexes = Knuckles_RightShoeIndices_DX;
		KnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
		KnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
		KnucklesWeldInfo[21].ModelB = KNUCKLES_OBJECTS[41];
		KnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftShoeIndices_DX) / 2);
		KnucklesWeldInfo[21].WeldType = 2;
		KnucklesWeldInfo[21].anonymous_5 = 0;
		KnucklesWeldInfo[21].VertexBuffer = 0;
		KnucklesWeldInfo[21].VertIndexes = Knuckles_LeftShoeIndices_DX;

		KnucklesWeldInfo[24].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[24].ModelA = KNUCKLES_OBJECTS[5];
		KnucklesWeldInfo[24].ModelB = 0;
		KnucklesWeldInfo[24].VertexPairCount = 2;
		KnucklesWeldInfo[24].WeldType = 4;
		KnucklesWeldInfo[24].anonymous_5 = 0;
		KnucklesWeldInfo[24].VertexBuffer = 0;
		KnucklesWeldInfo[24].VertIndexes = 0;
		KnucklesWeldInfo[25].BaseModel = *KNUCKLES_OBJECTS;
		KnucklesWeldInfo[25].ModelA = KNUCKLES_OBJECTS[9];
		KnucklesWeldInfo[25].ModelB = 0;
		KnucklesWeldInfo[25].VertexPairCount = 2;
		KnucklesWeldInfo[25].WeldType = 5;
		KnucklesWeldInfo[25].anonymous_5 = 0;
		KnucklesWeldInfo[25].VertexBuffer = 0;
		KnucklesWeldInfo[25].VertIndexes = 0;
		KnucklesWeldInfo[26].BaseModel = *KNUCKLES_OBJECTS;
		v3 = KNUCKLES_OBJECTS[17];
		KnucklesWeldInfo[26].ModelB = 0;
		KnucklesWeldInfo[26].VertexPairCount = 0;
		KnucklesWeldInfo[26].anonymous_5 = 0;
		KnucklesWeldInfo[26].VertexBuffer = 0;
		KnucklesWeldInfo[26].VertIndexes = 0;
		KnucklesWeldInfo[26].ModelA = v3;
		KnucklesWeldInfo[26].WeldType = 6;
		KnucklesWeldInfo[27].BaseModel = *KNUCKLES_OBJECTS;
		v4 = KNUCKLES_OBJECTS[19];
		KnucklesWeldInfo[27].ModelB = 0;
		KnucklesWeldInfo[27].VertexPairCount = 0;
		KnucklesWeldInfo[27].anonymous_5 = 0;
		KnucklesWeldInfo[27].VertexBuffer = 0;
		KnucklesWeldInfo[27].VertIndexes = 0;
		KnucklesWeldInfo[27].ModelA = v4;
		KnucklesWeldInfo[27].WeldType = 7;
		KnucklesWeldInfo[28].BaseModel = *KNUCKLES_OBJECTS;
		v5 = KNUCKLES_OBJECTS[54];
		KnucklesWeldInfo[28].ModelB = 0;
		KnucklesWeldInfo[28].VertexPairCount = 0;
		KnucklesWeldInfo[28].anonymous_5 = 0;
		KnucklesWeldInfo[28].VertexBuffer = 0;
		KnucklesWeldInfo[28].VertIndexes = 0;
		KnucklesWeldInfo[29].BaseModel = 0;
		KnucklesWeldInfo[29].ModelA = 0;
		KnucklesWeldInfo[29].ModelB = 0;
		KnucklesWeldInfo[29].VertexPairCount = 0;
		KnucklesWeldInfo[29].VertexBuffer = 0;
		KnucklesWeldInfo[28].ModelA = v5;
		KnucklesWeldInfo[28].WeldType = 8;
		KnucklesWeldInfo[29].VertIndexes = 0;
	}

	void __cdecl InitNPCKnucklesWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebx@1
		NJS_OBJECT* v4; // esi@1
		NJS_OBJECT* v5; // eax@1

		NPCKnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
		NPCKnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
		NPCKnucklesWeldInfo[0].anonymous_5 = 0;
		NPCKnucklesWeldInfo[0].VertexBuffer = 0;
		NPCKnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightUpperArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[0].WeldType = 2;
		NPCKnucklesWeldInfo[0].VertIndexes = Knuckles_RightUpperArmIndices_DX;
		NPCKnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
		NPCKnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
		NPCKnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLowerArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[1].WeldType = 2;
		NPCKnucklesWeldInfo[1].anonymous_5 = 0;
		NPCKnucklesWeldInfo[1].VertexBuffer = 0;
		NPCKnucklesWeldInfo[1].VertIndexes = Knuckles_RightLowerArmIndices_DX;
		NPCKnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
		v0 = KNUCKLES_OBJECTS[7];
		NPCKnucklesWeldInfo[2].VertIndexes = Knuckles_LeftUpperArmIndices_DX;
		NPCKnucklesWeldInfo[2].ModelB = v0;
		NPCKnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftUpperArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[2].WeldType = 2;
		NPCKnucklesWeldInfo[2].anonymous_5 = 0;
		NPCKnucklesWeldInfo[2].VertexBuffer = 0;
		NPCKnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
		NPCKnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
		NPCKnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLowerArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[3].WeldType = 2;
		NPCKnucklesWeldInfo[3].anonymous_5 = 0;
		NPCKnucklesWeldInfo[3].VertexBuffer = 0;
		NPCKnucklesWeldInfo[3].VertIndexes = Knuckles_LeftLowerArmIndices_DX;
		NPCKnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
		NPCKnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
		NPCKnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightKneeIndices_DX) / 2);
		NPCKnucklesWeldInfo[4].WeldType = 2;
		NPCKnucklesWeldInfo[4].anonymous_5 = 0;
		NPCKnucklesWeldInfo[4].VertexBuffer = 0;
		NPCKnucklesWeldInfo[4].VertIndexes = Knuckles_RightKneeIndices_DX;
		NPCKnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
		NPCKnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
		NPCKnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLegIndices_DX) / 2);
		NPCKnucklesWeldInfo[5].WeldType = 2;
		NPCKnucklesWeldInfo[5].anonymous_5 = 0;
		NPCKnucklesWeldInfo[5].VertexBuffer = 0;
		NPCKnucklesWeldInfo[5].VertIndexes = Knuckles_RightLegIndices_DX;
		NPCKnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
		NPCKnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
		NPCKnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftKneeIndices_DX) / 2);
		NPCKnucklesWeldInfo[6].WeldType = 2;
		NPCKnucklesWeldInfo[6].anonymous_5 = 0;
		NPCKnucklesWeldInfo[6].VertexBuffer = 0;
		NPCKnucklesWeldInfo[6].VertIndexes = Knuckles_LeftKneeIndices_DX;
		NPCKnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
		NPCKnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
		NPCKnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLegIndices_DX) / 2);
		NPCKnucklesWeldInfo[7].WeldType = 2;
		NPCKnucklesWeldInfo[7].anonymous_5 = 0;
		NPCKnucklesWeldInfo[7].VertexBuffer = 0;
		NPCKnucklesWeldInfo[7].VertIndexes = Knuckles_LeftLegIndices_DX;
		NPCKnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
		NPCKnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
		NPCKnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightShoeIndices_DX) / 2);
		NPCKnucklesWeldInfo[8].WeldType = 2;
		NPCKnucklesWeldInfo[8].anonymous_5 = 0;
		NPCKnucklesWeldInfo[8].VertexBuffer = 0;
		NPCKnucklesWeldInfo[8].VertIndexes = Knuckles_RightShoeIndices_DX;
		NPCKnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
		NPCKnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
		v1 = KNUCKLES_OBJECTS[19];
		NPCKnucklesWeldInfo[9].VertIndexes = Knuckles_LeftShoeIndices_DX;
		NPCKnucklesWeldInfo[9].ModelB = v1;
		NPCKnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftShoeIndices_DX) / 2);
		NPCKnucklesWeldInfo[9].WeldType = 2;
		NPCKnucklesWeldInfo[9].anonymous_5 = 0;
		NPCKnucklesWeldInfo[9].VertexBuffer = 0;

		NPCKnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
		NPCKnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
		NPCKnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightUpperArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[12].WeldType = 2;
		NPCKnucklesWeldInfo[12].anonymous_5 = 0;
		NPCKnucklesWeldInfo[12].VertexBuffer = 0;
		NPCKnucklesWeldInfo[12].VertIndexes = Knuckles_RightUpperArmIndices_DX;
		NPCKnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
		NPCKnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
		NPCKnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLowerArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[13].WeldType = 2;
		NPCKnucklesWeldInfo[13].anonymous_5 = 0;
		NPCKnucklesWeldInfo[13].VertexBuffer = 0;
		NPCKnucklesWeldInfo[13].VertIndexes = Knuckles_RightLowerArmIndices_DX;
		NPCKnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
		NPCKnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
		NPCKnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftUpperArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[14].WeldType = 2;
		NPCKnucklesWeldInfo[14].anonymous_5 = 0;
		NPCKnucklesWeldInfo[14].VertexBuffer = 0;
		NPCKnucklesWeldInfo[14].VertIndexes = Knuckles_LeftUpperArmIndices_DX;
		NPCKnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
		NPCKnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
		NPCKnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLowerArmIndices_DX) / 2);
		NPCKnucklesWeldInfo[15].WeldType = 2;
		NPCKnucklesWeldInfo[15].anonymous_5 = 0;
		NPCKnucklesWeldInfo[15].VertexBuffer = 0;
		NPCKnucklesWeldInfo[15].VertIndexes = Knuckles_LeftLowerArmIndices_DX;
		NPCKnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
		NPCKnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
		NPCKnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightKneeIndices_DX) / 2);
		NPCKnucklesWeldInfo[16].WeldType = 2;
		NPCKnucklesWeldInfo[16].anonymous_5 = 0;
		NPCKnucklesWeldInfo[16].VertexBuffer = 0;
		NPCKnucklesWeldInfo[16].VertIndexes = Knuckles_RightKneeIndices_DX;
		NPCKnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
		NPCKnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
		NPCKnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightLegIndices_DX) / 2);
		NPCKnucklesWeldInfo[17].WeldType = 2;
		NPCKnucklesWeldInfo[17].anonymous_5 = 0;
		NPCKnucklesWeldInfo[17].VertexBuffer = 0;
		NPCKnucklesWeldInfo[17].VertIndexes = Knuckles_RightLegIndices_DX;
		NPCKnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
		NPCKnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
		NPCKnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftKneeIndices_DX) / 2);
		NPCKnucklesWeldInfo[18].WeldType = 2;
		NPCKnucklesWeldInfo[18].anonymous_5 = 0;
		NPCKnucklesWeldInfo[18].VertexBuffer = 0;
		NPCKnucklesWeldInfo[18].VertIndexes = Knuckles_LeftKneeIndices_DX;
		NPCKnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
		v2 = KNUCKLES_OBJECTS[37];
		NPCKnucklesWeldInfo[19].anonymous_5 = 0;
		NPCKnucklesWeldInfo[19].VertexBuffer = 0;
		NPCKnucklesWeldInfo[19].VertIndexes = Knuckles_LeftLegIndices_DX;
		NPCKnucklesWeldInfo[19].ModelB = v2;
		NPCKnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftLegIndices_DX) / 2);
		NPCKnucklesWeldInfo[19].WeldType = 2;
		NPCKnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
		NPCKnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
		NPCKnucklesWeldInfo[20].anonymous_5 = 0;
		NPCKnucklesWeldInfo[20].VertexBuffer = 0;
		NPCKnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_RightShoeIndices_DX) / 2);
		NPCKnucklesWeldInfo[20].WeldType = 2;
		NPCKnucklesWeldInfo[20].VertIndexes = Knuckles_RightShoeIndices_DX;
		NPCKnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
		NPCKnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
		v3 = KNUCKLES_OBJECTS[41];
		NPCKnucklesWeldInfo[21].anonymous_5 = 0;
		NPCKnucklesWeldInfo[21].VertexBuffer = 0;
		NPCKnucklesWeldInfo[21].ModelB = v3;
		NPCKnucklesWeldInfo[21].VertIndexes = Knuckles_LeftShoeIndices_DX;
		NPCKnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LeftShoeIndices_DX) / 2);
		NPCKnucklesWeldInfo[21].WeldType = 2;

	}

	void Init_Sonic()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___SONIC_OBJECTS");

		WriteJump((void*)0x007D0B50, InitSonicWeldInfo_mod);
		WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_mod);
		WriteData((NJS_OBJECT**)0x00664C3E, &object_029D8708);
		WriteData((NJS_OBJECT**)0x0069E24B, &object_029D8708);
		WriteData((NJS_OBJECT**)0x006D010C, &object_029D8708);
		WriteData((NJS_OBJECT**)0x006D711E, &object_029D8708);
	}

	void Init_Amy()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** AMY_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___AMY_OBJECTS");

		WriteJump((void*)0x007CCB90, InitAmyWeldInfo_mod);
		WriteJump((void*)0x007CD000, InitNPCAmyWeldInfo_mod);
	}

	void Init_Tails()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** MILES_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___MILES_OBJECTS");

		WriteJump((void*)0x007C6D80, InitTailsWeldInfo_mod);
		WriteJump((void*)0x007C7560, InitNPCTailsWeldInfo_mod);
	}

	void Init_Knuckles()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** KNUCKLES_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___KNUCKLES_OBJECTS");

		WriteJump((void*)0x007C94D0, InitKnucklesWeldInfo_mod);
		WriteJump((void*)0x007C9C80, InitNPCKnucklesWeldInfo_mod);
	}

	__declspec(dllexport) __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
	//Welding
		Init_Sonic();
		Init_Amy();
		Init_Tails();
		Init_Knuckles();
	//Disable morphs
		WriteData<3>((void*)0x45BB60, 0x90u);
		WriteData<3>((void*)0x45B821, 0x90u);
		WriteData<3>((void*)0x45BB74, 0x90u);
		WriteData<3>((void*)0x45B821, 0x90u);
		WriteData<3>((void*)0x45BED3, 0x90u);
		WriteData<3>((void*)0x45DAB1, 0x90u);
		WriteData<3>((void*)0x461389, 0x90u);
		WriteData<3>((void*)0x461325, 0x90u);
		WriteData<3>((void*)0x45BEE7, 0x90u);
		WriteData<3>((void*)0x45DACA, 0x90u);
		WriteData<3>((void*)0x4613A1, 0x90u);
		WriteData<3>((void*)0x461339, 0x90u);
		WriteData<3>((void*)0x473FB2, 0x90u);
		WriteData<3>((void*)0x473CC1, 0x90u);
		WriteData<3>((void*)0x473FC7, 0x90u);
		WriteData<3>((void*)0x473CD5, 0x90u);

	//Functions
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	std::string SSText_String = "Upgraded";
	SSText_String = config->getString("Textures", "SS", "Upgraded");
	if (SSText_String == "Dreamcast") SSText = Dreamcast;
	if (SSText_String == "Upgraded") SSText = Upgraded;

	//Replace textures
	ReplacePVM("sonic", "sonicnm");
	ReplacePVM("Miles", "Milesnm")
	ReplacePVM("knuckles", "knucklesnm")
	ReplacePVM("amy", "amynm")

	if (SSText == Dreamcast)
	{
		ReplacePVM("supersonic", "supersonicnmc")
	}

	if (SSText == Upgraded)
	{
		ReplacePVM("supersonic", "supersonicnm")
	}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}