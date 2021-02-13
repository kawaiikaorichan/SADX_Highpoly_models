#include "SADXModLoader.h"
#include <stdio.h>
#include "IniFile.hpp"
#include "pch.h"
#include <cmath>
#include "stdafx.h"

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
		SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[10].ModelA = SONIC_OBJECTS[4];
		SonicWeldInfo[10].ModelB = SONIC_OBJECTS[5];
		SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightHandIndices_DX) / 2);
		SonicWeldInfo[10].WeldType = 2;
		SonicWeldInfo[10].anonymous_5 = 0;
		SonicWeldInfo[10].VertexBuffer = 0;
		SonicWeldInfo[10].VertIndexes = Sonic_RightHandIndices_DX;
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
		NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
		NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
		NPCSonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_RightHandIndices_DX) / 2);
		NPCSonicWeldInfo[11].WeldType = 2;
		NPCSonicWeldInfo[11].anonymous_5 = 0;
		NPCSonicWeldInfo[11].VertexBuffer = 0;
		NPCSonicWeldInfo[11].VertIndexes = Sonic_RightHandIndices_DX;
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

	void Init_Sonic()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___SONIC_OBJECTS");

		WriteJump((void*)0x007D0B50, InitSonicWeldInfo_mod);
		WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_mod);
	}

	void Init_Amy()
	{
		HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** AMY_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___AMY_OBJECTS");

		WriteJump((void*)0x007CCB90, InitAmyWeldInfo_mod);
		WriteJump((void*)0x007CD000, InitNPCAmyWeldInfo_mod);
	}

	__declspec(dllexport) __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
	//Welding
		Init_Sonic();
		Init_Amy();
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