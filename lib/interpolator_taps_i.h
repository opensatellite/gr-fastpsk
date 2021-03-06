/*
 * This file was generated by gen_interpolator_taps.
 */

static const int	hb_ntaps  =    8;
static const int	hb_nsteps =  128;
static const double	hb_bw     = 0.25;

static const int hb_taps[hb_nsteps+1][hb_ntaps] = {
  //    -4            -3            -2            -1             0             1             2             3                mu
  {        0,        0,        0,        0,    32767,        0,        0,        0 }, //   0/128
  {       -5,       28,      -91,      259,    32719,     -177,       41,       -7 }, //   1/128
  {      -10,       56,     -182,      520,    32665,     -351,       81,      -13 }, //   2/128
  {      -15,       84,     -273,      785,    32606,     -522,      121,      -19 }, //   3/128
  {      -20,      112,     -365,     1054,    32540,     -689,      161,      -26 }, //   4/128
  {      -25,      140,     -457,     1325,    32469,     -853,      200,      -32 }, //   5/128
  {      -30,      168,     -550,     1599,    32393,    -1014,      238,      -38 }, //   6/128
  {      -35,      196,     -642,     1876,    32311,    -1172,      276,      -44 }, //   7/128
  {      -40,      224,     -735,     2156,    32223,    -1325,      314,      -51 }, //   8/128
  {      -45,      252,     -827,     2438,    32129,    -1476,      350,      -57 }, //   9/128
  {      -50,      280,     -920,     2723,    32031,    -1623,      387,      -62 }, //  10/128
  {      -55,      308,    -1013,     3011,    31926,    -1767,      423,      -68 }, //  11/128
  {      -60,      335,    -1105,     3302,    31816,    -1908,      458,      -74 }, //  12/128
  {      -65,      363,    -1198,     3595,    31701,    -2045,      492,      -80 }, //  13/128
  {      -70,      390,    -1290,     3890,    31581,    -2178,      526,      -85 }, //  14/128
  {      -75,      418,    -1382,     4188,    31455,    -2308,      560,      -91 }, //  15/128
  {      -80,      445,    -1474,     4488,    31324,    -2435,      592,      -96 }, //  16/128
  {      -84,      472,    -1566,     4790,    31187,    -2558,      624,     -102 }, //  17/128
  {      -89,      498,    -1657,     5095,    31046,    -2678,      656,     -107 }, //  18/128
  {      -94,      525,    -1748,     5401,    30899,    -2795,      687,     -112 }, //  19/128
  {      -98,      551,    -1839,     5709,    30748,    -2908,      717,     -117 }, //  20/128
  {     -103,      577,    -1929,     6020,    30591,    -3017,      746,     -122 }, //  21/128
  {     -108,      603,    -2018,     6332,    30429,    -3124,      775,     -127 }, //  22/128
  {     -112,      629,    -2107,     6646,    30262,    -3226,      803,     -132 }, //  23/128
  {     -116,      654,    -2195,     6961,    30091,    -3326,      830,     -137 }, //  24/128
  {     -121,      679,    -2283,     7278,    29915,    -3422,      857,     -141 }, //  25/128
  {     -125,      704,    -2370,     7597,    29733,    -3514,      882,     -145 }, //  26/128
  {     -129,      728,    -2456,     7917,    29548,    -3604,      908,     -150 }, //  27/128
  {     -133,      752,    -2541,     8238,    29357,    -3689,      932,     -154 }, //  28/128
  {     -138,      776,    -2626,     8561,    29162,    -3772,      956,     -158 }, //  29/128
  {     -142,      799,    -2710,     8885,    28963,    -3851,      978,     -162 }, //  30/128
  {     -146,      822,    -2792,     9209,    28758,    -3927,     1001,     -166 }, //  31/128
  {     -149,      845,    -2874,     9535,    28550,    -3999,     1022,     -170 }, //  32/128
  {     -153,      867,    -2954,     9862,    28337,    -4068,     1042,     -173 }, //  33/128
  {     -157,      889,    -3034,    10190,    28120,    -4134,     1062,     -177 }, //  34/128
  {     -161,      910,    -3112,    10518,    27899,    -4196,     1081,     -180 }, //  35/128
  {     -164,      931,    -3189,    10847,    27674,    -4256,     1100,     -183 }, //  36/128
  {     -168,      952,    -3265,    11177,    27444,    -4312,     1117,     -187 }, //  37/128
  {     -171,      972,    -3339,    11507,    27211,    -4364,     1134,     -190 }, //  38/128
  {     -174,      991,    -3413,    11838,    26973,    -4414,     1150,     -192 }, //  39/128
  {     -177,     1010,    -3485,    12169,    26732,    -4460,     1165,     -195 }, //  40/128
  {     -181,     1029,    -3555,    12500,    26487,    -4503,     1179,     -198 }, //  41/128
  {     -184,     1047,    -3624,    12831,    26238,    -4543,     1193,     -200 }, //  42/128
  {     -186,     1064,    -3691,    13163,    25986,    -4580,     1206,     -203 }, //  43/128
  {     -189,     1081,    -3757,    13494,    25730,    -4613,     1218,     -205 }, //  44/128
  {     -192,     1098,    -3821,    13825,    25471,    -4644,     1229,     -207 }, //  45/128
  {     -195,     1114,    -3884,    14157,    25208,    -4671,     1239,     -209 }, //  46/128
  {     -197,     1129,    -3945,    14487,    24942,    -4696,     1249,     -211 }, //  47/128
  {     -199,     1144,    -4004,    14818,    24672,    -4717,     1258,     -213 }, //  48/128
  {     -202,     1158,    -4061,    15148,    24400,    -4736,     1266,     -214 }, //  49/128
  {     -204,     1171,    -4116,    15477,    24124,    -4751,     1273,     -216 }, //  50/128
  {     -206,     1184,    -4170,    15806,    23845,    -4764,     1279,     -217 }, //  51/128
  {     -208,     1197,    -4221,    16134,    23563,    -4774,     1285,     -218 }, //  52/128
  {     -210,     1208,    -4271,    16461,    23279,    -4780,     1290,     -219 }, //  53/128
  {     -211,     1219,    -4319,    16788,    22991,    -4784,     1294,     -220 }, //  54/128
  {     -213,     1230,    -4364,    17113,    22701,    -4785,     1297,     -221 }, //  55/128
  {     -215,     1240,    -4408,    17437,    22409,    -4784,     1300,     -221 }, //  56/128
  {     -216,     1249,    -4449,    17761,    22113,    -4779,     1302,     -222 }, //  57/128
  {     -217,     1257,    -4488,    18082,    21816,    -4772,     1303,     -222 }, //  58/128
  {     -218,     1265,    -4525,    18403,    21516,    -4762,     1303,     -223 }, //  59/128
  {     -219,     1272,    -4560,    18722,    21213,    -4750,     1302,     -223 }, //  60/128
  {     -220,     1278,    -4592,    19040,    20909,    -4735,     1301,     -223 }, //  61/128
  {     -221,     1284,    -4622,    19356,    20602,    -4717,     1299,     -223 }, //  62/128
  {     -222,     1289,    -4649,    19670,    20293,    -4697,     1296,     -222 }, //  63/128
  {     -222,     1293,    -4674,    19983,    19983,    -4674,     1293,     -222 }, //  64/128
  {     -222,     1296,    -4697,    20293,    19670,    -4649,     1289,     -222 }, //  65/128
  {     -223,     1299,    -4717,    20602,    19356,    -4622,     1284,     -221 }, //  66/128
  {     -223,     1301,    -4735,    20909,    19040,    -4592,     1278,     -220 }, //  67/128
  {     -223,     1302,    -4750,    21213,    18722,    -4560,     1272,     -219 }, //  68/128
  {     -223,     1303,    -4762,    21516,    18403,    -4525,     1265,     -218 }, //  69/128
  {     -222,     1303,    -4772,    21816,    18082,    -4488,     1257,     -217 }, //  70/128
  {     -222,     1302,    -4779,    22113,    17761,    -4449,     1249,     -216 }, //  71/128
  {     -221,     1300,    -4784,    22409,    17437,    -4408,     1240,     -215 }, //  72/128
  {     -221,     1297,    -4785,    22701,    17113,    -4364,     1230,     -213 }, //  73/128
  {     -220,     1294,    -4784,    22991,    16788,    -4319,     1219,     -211 }, //  74/128
  {     -219,     1290,    -4780,    23279,    16461,    -4271,     1208,     -210 }, //  75/128
  {     -218,     1285,    -4774,    23563,    16134,    -4221,     1197,     -208 }, //  76/128
  {     -217,     1279,    -4764,    23845,    15806,    -4170,     1184,     -206 }, //  77/128
  {     -216,     1273,    -4751,    24124,    15477,    -4116,     1171,     -204 }, //  78/128
  {     -214,     1266,    -4736,    24400,    15148,    -4061,     1158,     -202 }, //  79/128
  {     -213,     1258,    -4717,    24672,    14818,    -4004,     1144,     -199 }, //  80/128
  {     -211,     1249,    -4696,    24942,    14487,    -3945,     1129,     -197 }, //  81/128
  {     -209,     1239,    -4671,    25208,    14157,    -3884,     1114,     -195 }, //  82/128
  {     -207,     1229,    -4644,    25471,    13825,    -3821,     1098,     -192 }, //  83/128
  {     -205,     1218,    -4613,    25730,    13494,    -3757,     1081,     -189 }, //  84/128
  {     -203,     1206,    -4580,    25986,    13163,    -3691,     1064,     -186 }, //  85/128
  {     -200,     1193,    -4543,    26238,    12831,    -3624,     1047,     -184 }, //  86/128
  {     -198,     1179,    -4503,    26487,    12500,    -3555,     1029,     -181 }, //  87/128
  {     -195,     1165,    -4460,    26732,    12169,    -3485,     1010,     -177 }, //  88/128
  {     -192,     1150,    -4414,    26973,    11838,    -3413,      991,     -174 }, //  89/128
  {     -190,     1134,    -4364,    27211,    11507,    -3339,      972,     -171 }, //  90/128
  {     -187,     1117,    -4312,    27444,    11177,    -3265,      952,     -168 }, //  91/128
  {     -183,     1100,    -4256,    27674,    10847,    -3189,      931,     -164 }, //  92/128
  {     -180,     1081,    -4196,    27899,    10518,    -3112,      910,     -161 }, //  93/128
  {     -177,     1062,    -4134,    28120,    10190,    -3034,      889,     -157 }, //  94/128
  {     -173,     1042,    -4068,    28337,     9862,    -2954,      867,     -153 }, //  95/128
  {     -170,     1022,    -3999,    28550,     9535,    -2874,      845,     -149 }, //  96/128
  {     -166,     1001,    -3927,    28758,     9209,    -2792,      822,     -146 }, //  97/128
  {     -162,      978,    -3851,    28963,     8885,    -2710,      799,     -142 }, //  98/128
  {     -158,      956,    -3772,    29162,     8561,    -2626,      776,     -138 }, //  99/128
  {     -154,      932,    -3689,    29357,     8238,    -2541,      752,     -133 }, // 100/128
  {     -150,      908,    -3604,    29548,     7917,    -2456,      728,     -129 }, // 101/128
  {     -145,      882,    -3514,    29733,     7597,    -2370,      704,     -125 }, // 102/128
  {     -141,      857,    -3422,    29915,     7278,    -2283,      679,     -121 }, // 103/128
  {     -137,      830,    -3326,    30091,     6961,    -2195,      654,     -116 }, // 104/128
  {     -132,      803,    -3226,    30262,     6646,    -2107,      629,     -112 }, // 105/128
  {     -127,      775,    -3124,    30429,     6332,    -2018,      603,     -108 }, // 106/128
  {     -122,      746,    -3017,    30591,     6020,    -1929,      577,     -103 }, // 107/128
  {     -117,      717,    -2908,    30748,     5709,    -1839,      551,      -98 }, // 108/128
  {     -112,      687,    -2795,    30899,     5401,    -1748,      525,      -94 }, // 109/128
  {     -107,      656,    -2678,    31046,     5095,    -1657,      498,      -89 }, // 110/128
  {     -102,      624,    -2558,    31187,     4790,    -1566,      472,      -84 }, // 111/128
  {      -96,      592,    -2435,    31324,     4488,    -1474,      445,      -80 }, // 112/128
  {      -91,      560,    -2308,    31455,     4188,    -1382,      418,      -75 }, // 113/128
  {      -85,      526,    -2178,    31581,     3890,    -1290,      390,      -70 }, // 114/128
  {      -80,      492,    -2045,    31701,     3595,    -1198,      363,      -65 }, // 115/128
  {      -74,      458,    -1908,    31816,     3302,    -1105,      335,      -60 }, // 116/128
  {      -68,      423,    -1767,    31926,     3011,    -1013,      308,      -55 }, // 117/128
  {      -62,      387,    -1623,    32031,     2723,     -920,      280,      -50 }, // 118/128
  {      -57,      350,    -1476,    32129,     2438,     -827,      252,      -45 }, // 119/128
  {      -51,      314,    -1325,    32223,     2156,     -735,      224,      -40 }, // 120/128
  {      -44,      276,    -1172,    32311,     1876,     -642,      196,      -35 }, // 121/128
  {      -38,      238,    -1014,    32393,     1599,     -550,      168,      -30 }, // 122/128
  {      -32,      200,     -853,    32469,     1325,     -457,      140,      -25 }, // 123/128
  {      -26,      161,     -689,    32540,     1054,     -365,      112,      -20 }, // 124/128
  {      -19,      121,     -522,    32606,      785,     -273,       84,      -15 }, // 125/128
  {      -13,       81,     -351,    32665,      520,     -182,       56,      -10 }, // 126/128
  {       -7,       41,     -177,    32719,      259,      -91,       28,       -5 }, // 127/128
  {        0,        0,        0,    32767,        0,        0,        0,        0 }, // 128/128
};

