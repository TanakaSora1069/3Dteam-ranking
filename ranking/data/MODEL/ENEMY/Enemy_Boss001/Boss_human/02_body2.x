xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 71;
 0.00000;3.13943;-0.17536;,
 8.22194;3.13943;-3.85618;,
 0.00000;4.76658;-7.53700;,
 0.00000;3.13943;-0.17536;,
 8.55664;3.96441;3.50547;,
 0.00000;3.13943;-0.17536;,
 0.00000;6.51623;8.49556;,
 0.00000;3.13943;-0.17536;,
 -8.55664;3.96441;3.50547;,
 0.00000;3.13943;-0.17536;,
 -8.22194;3.13943;-3.85618;,
 0.00000;3.13943;-0.17536;,
 0.00000;4.76658;-7.53700;,
 3.23928;-8.61746;-2.94022;,
 0.00000;-9.20158;-0.17536;,
 0.00000;-10.64987;-6.41597;,
 0.00000;-3.39848;-7.07634;,
 4.63316;-3.39848;-2.82376;,
 3.24936;-6.54650;2.58750;,
 0.00000;-9.20158;-0.17536;,
 3.23928;-8.61746;-2.94022;,
 4.63316;-3.39848;2.47305;,
 0.00000;-6.53773;5.01006;,
 0.00000;-9.20158;-0.17536;,
 3.24936;-6.54650;2.58750;,
 0.00000;-3.39848;6.25978;,
 -3.24936;-6.54650;2.58750;,
 0.00000;-9.20158;-0.17536;,
 0.00000;-6.53773;5.01006;,
 -4.63316;-3.39848;2.47305;,
 -3.23928;-8.61746;-2.94022;,
 0.00000;-9.20158;-0.17536;,
 -3.24936;-6.54650;2.58750;,
 -4.63316;-3.39848;-2.82376;,
 0.00000;-10.64987;-6.41597;,
 0.00000;-9.20158;-0.17536;,
 -3.23928;-8.61746;-2.94022;,
 0.00000;-3.39848;-7.07634;,
 9.65706;0.25073;-3.68441;,
 0.00000;0.26772;-7.09533;,
 11.17701;1.04182;3.32976;,
 0.00000;1.02494;6.72831;,
 -11.17701;1.04182;3.32976;,
 -9.65706;0.25073;-3.68441;,
 0.00000;0.26772;-7.09533;,
 9.74491;-5.05023;-2.40939;,
 9.74491;-6.76613;-1.40879;,
 -9.74491;-6.76613;-1.40879;,
 -9.74491;-5.05023;-2.40939;,
 9.74491;-6.76613;0.59241;,
 -9.74491;-6.76613;0.59241;,
 9.74491;-5.05023;1.59302;,
 -9.74491;-5.05023;1.59302;,
 9.74491;-3.33433;0.59241;,
 -9.74491;-3.33433;0.59241;,
 9.74491;-3.33433;-1.40879;,
 -9.74491;-3.33433;-1.40879;,
 9.74491;-5.05023;-2.40939;,
 -9.74491;-5.05023;-2.40939;,
 9.74491;-5.05023;-0.40819;,
 9.74491;-5.05023;-0.40819;,
 9.74491;-5.05023;-0.40819;,
 9.74491;-5.05023;-0.40819;,
 9.74491;-5.05023;-0.40819;,
 9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;,
 -9.74491;-5.05023;-0.40819;;
 
 48;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,15;,
 4;13,15,16,17;,
 3;18,19,20;,
 4;18,20,17,21;,
 3;22,23,24;,
 4;22,24,21,25;,
 3;26,27,28;,
 4;26,28,25,29;,
 3;30,31,32;,
 4;30,32,29,33;,
 3;34,35,36;,
 4;34,36,33,37;,
 4;38,17,16,39;,
 4;38,39,2,1;,
 4;40,21,17,38;,
 4;40,38,1,4;,
 4;41,25,21,40;,
 4;41,40,4,6;,
 4;42,29,25,41;,
 4;42,41,6,8;,
 4;43,33,29,42;,
 4;43,42,8,10;,
 4;44,37,33,43;,
 4;44,43,10,12;,
 4;45,46,47,48;,
 4;46,49,50,47;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 3;59,46,45;,
 3;60,49,46;,
 3;61,51,49;,
 3;62,53,51;,
 3;63,55,53;,
 3;64,57,55;,
 3;65,48,47;,
 3;66,47,50;,
 3;67,50,52;,
 3;68,52,54;,
 3;69,54,56;,
 3;70,56,58;;
 
 MeshMaterialList {
  12;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.671200;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.132000;0.132000;0.132000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.084800;0.021600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.040800;0.552000;0.037600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.696800;0.680800;0.238400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558400;0.558400;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.496000;0.360800;0.244800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.724800;0.674400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.125600;0.414400;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.000000;0.996102;-0.088208;,
  0.000000;0.976433;0.215822;,
  0.324570;0.945505;-0.025966;,
  0.309975;0.919886;-0.240259;,
  0.000000;0.931831;-0.362893;,
  -0.309975;0.919886;-0.240259;,
  -0.324570;0.945505;-0.025966;,
  0.614775;-0.208747;-0.760576;,
  0.786645;-0.449523;-0.423224;,
  0.733976;-0.496850;0.463055;,
  0.223424;-0.342266;0.912653;,
  -0.733976;-0.496850;0.463055;,
  -0.786645;-0.449523;-0.423224;,
  -0.000000;-0.938072;0.346441;,
  0.000000;-0.974112;0.226068;,
  0.618867;-0.757281;0.208636;,
  0.634628;-0.639803;0.433473;,
  0.000000;-0.683795;0.729674;,
  -0.634628;-0.639803;0.433473;,
  -0.618867;-0.757281;0.208636;,
  -0.000000;-0.165473;-0.986214;,
  0.442397;-0.148400;-0.884456;,
  0.554012;-0.464812;0.690666;,
  0.000000;-0.198949;0.980010;,
  -0.417111;-0.180816;0.890688;,
  -0.571666;-0.438552;-0.693448;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.503741;-0.863854;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.503745;0.863852;,
  0.000000;0.503748;0.863851;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.709283;-0.111409;-0.696065;,
  -0.591842;-0.273581;0.758206;,
  -0.709283;-0.111409;-0.696065;,
  -0.614775;-0.208747;-0.760576;,
  0.000000;0.010225;-0.999948;,
  0.363646;0.009525;-0.931488;,
  0.575895;-0.817394;-0.014552;,
  0.816153;0.550743;-0.174862;,
  0.364416;-0.040765;0.930344;,
  0.000000;-0.043775;0.999041;,
  -0.364416;-0.040765;0.930344;,
  -0.575895;-0.817394;-0.014552;,
  -0.816153;0.550743;-0.174862;,
  -0.363646;0.009525;-0.931488;,
  0.000000;0.503744;-0.863853;;
  48;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  3;15,13,14;,
  4;33,33,7,8;,
  3;16,13,15;,
  4;16,15,8,9;,
  3;17,13,16;,
  4;17,16,9,10;,
  3;18,13,17;,
  4;18,17,34,11;,
  3;19,13,18;,
  4;19,18,11,12;,
  3;14,13,19;,
  4;35,35,12,36;,
  4;21,8,7,20;,
  4;21,20,37,38;,
  4;22,9,8,39;,
  4;40,40,2,3;,
  4;23,10,9,22;,
  4;23,22,41,42;,
  4;24,11,10,23;,
  4;24,23,42,43;,
  4;25,12,11,44;,
  4;45,45,5,6;,
  4;20,36,12,25;,
  4;20,25,46,37;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;47,47,47,47;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;32,32,32;,
  3;32,32,32;,
  3;32,32,32;,
  3;32,32,32;,
  3;32,32,32;,
  3;32,32,32;;
 }
 MeshTextureCoords {
  71;
  0.083330;0.000000;,
  0.166670;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.333330;0.000000;,
  0.416670;0.000000;,
  0.500000;0.000000;,
  0.583330;0.000000;,
  0.666670;0.000000;,
  0.750000;0.000000;,
  0.833330;0.000000;,
  0.916670;0.000000;,
  1.000000;0.000000;,
  0.126530;1.000000;,
  0.083330;1.000000;,
  0.040210;1.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.293330;1.000000;,
  0.250000;1.000000;,
  0.206810;1.000000;,
  0.333330;1.000000;,
  0.460060;1.000000;,
  0.416670;1.000000;,
  0.373340;1.000000;,
  0.500000;1.000000;,
  0.626660;1.000000;,
  0.583330;1.000000;,
  0.539940;1.000000;,
  0.666670;1.000000;,
  0.793190;1.000000;,
  0.750000;1.000000;,
  0.706670;1.000000;,
  0.833330;1.000000;,
  0.959790;1.000000;,
  0.916670;1.000000;,
  0.873470;1.000000;,
  1.000000;1.000000;,
  0.166670;0.441840;,
  0.000000;0.439240;,
  0.333330;0.447020;,
  0.500000;0.449600;,
  0.666670;0.447020;,
  0.833330;0.441840;,
  1.000000;0.439240;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}