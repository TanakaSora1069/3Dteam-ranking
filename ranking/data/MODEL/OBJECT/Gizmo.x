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
 122;
 0.00000;38.75046;-1.24954;,
 0.00000;41.24954;0.00000;,
 1.24954;38.75046;0.00000;,
 0.00000;41.24954;0.00000;,
 0.00000;38.75046;1.24954;,
 0.00000;41.24954;0.00000;,
 -1.24954;38.75046;0.00000;,
 0.00000;41.24954;0.00000;,
 0.00000;38.75046;-1.24954;,
 0.00000;38.75046;0.00000;,
 0.00000;38.75046;-1.24954;,
 1.24954;38.75046;0.00000;,
 0.00000;38.75046;1.24954;,
 -1.24954;38.75046;0.00000;,
 0.00000;-1.24954;-38.75046;,
 0.00000;0.00000;-41.24954;,
 1.24954;0.00000;-38.75046;,
 0.00000;0.00000;-41.24954;,
 0.00000;1.24954;-38.75046;,
 0.00000;0.00000;-41.24954;,
 -1.24954;0.00000;-38.75046;,
 0.00000;0.00000;-41.24954;,
 0.00000;-1.24954;-38.75046;,
 0.00000;0.00000;-38.75046;,
 0.00000;-1.24954;-38.75046;,
 1.24954;0.00000;-38.75046;,
 0.00000;1.24954;-38.75046;,
 -1.24954;0.00000;-38.75046;,
 38.75046;-1.24954;-0.00000;,
 41.24954;0.00000;0.00000;,
 38.75046;0.00000;1.24954;,
 41.24954;0.00000;0.00000;,
 38.75046;1.24954;0.00000;,
 41.24954;0.00000;0.00000;,
 38.75046;0.00000;-1.24954;,
 41.24954;0.00000;0.00000;,
 38.75046;-1.24954;-0.00000;,
 38.75046;0.00000;0.00000;,
 38.75046;-1.24954;-0.00000;,
 38.75046;0.00000;1.24954;,
 38.75046;1.24954;0.00000;,
 38.75046;0.00000;-1.24954;,
 -0.98352;0.98352;-0.98352;,
 0.98352;0.98352;-0.98352;,
 0.98352;-0.98352;-0.98352;,
 -0.98352;-0.98352;-0.98352;,
 0.98352;0.98352;-0.98352;,
 0.98352;0.98352;0.98352;,
 0.98352;-0.98352;0.98352;,
 0.98352;-0.98352;-0.98352;,
 0.98352;0.98352;0.98352;,
 -0.98352;0.98352;0.98352;,
 -0.98352;-0.98352;0.98352;,
 0.98352;-0.98352;0.98352;,
 -0.98352;0.98352;0.98352;,
 -0.98352;0.98352;-0.98352;,
 -0.98352;-0.98352;-0.98352;,
 -0.98352;-0.98352;0.98352;,
 0.98352;0.98352;-0.98352;,
 -0.98352;0.98352;-0.98352;,
 -0.98352;-0.98352;-0.98352;,
 0.98352;-0.98352;-0.98352;,
 -0.14062;0.14062;-39.27834;,
 0.14062;0.14062;-39.27834;,
 0.14062;-0.14062;-39.27834;,
 -0.14062;-0.14062;-39.27834;,
 0.14062;0.14062;-39.27834;,
 0.14062;0.14062;-0.45290;,
 0.14062;-0.14062;-0.45290;,
 0.14062;-0.14062;-39.27834;,
 0.14062;0.14062;-0.45290;,
 -0.14062;0.14062;-0.45290;,
 -0.14062;-0.14062;-0.45290;,
 0.14062;-0.14062;-0.45290;,
 -0.14062;0.14062;-0.45290;,
 -0.14062;0.14062;-39.27834;,
 -0.14062;-0.14062;-39.27834;,
 -0.14062;-0.14062;-0.45290;,
 0.14062;0.14062;-39.27834;,
 -0.14062;0.14062;-39.27834;,
 -0.14062;-0.14062;-39.27834;,
 0.14062;-0.14062;-39.27834;,
 39.86966;0.14062;-0.14062;,
 39.86966;0.14062;0.14062;,
 39.86966;-0.14062;0.14062;,
 39.86966;-0.14062;-0.14062;,
 39.86966;0.14062;0.14062;,
 0.65502;0.14062;0.14062;,
 0.65502;-0.14062;0.14062;,
 39.86966;-0.14062;0.14062;,
 0.65502;0.14062;0.14062;,
 0.65502;0.14062;-0.14062;,
 0.65502;-0.14062;-0.14062;,
 0.65502;-0.14062;0.14062;,
 0.65502;0.14062;-0.14062;,
 39.86966;0.14062;-0.14062;,
 39.86966;-0.14062;-0.14062;,
 0.65502;-0.14062;-0.14062;,
 39.86966;0.14062;0.14062;,
 39.86966;0.14062;-0.14062;,
 39.86966;-0.14062;-0.14062;,
 39.86966;-0.14062;0.14062;,
 0.14062;39.19822;-0.14062;,
 -0.14062;39.19822;-0.14062;,
 -0.14062;39.19822;0.14062;,
 0.14062;39.19822;0.14062;,
 -0.14062;39.19822;-0.14062;,
 -0.14062;-0.80662;-0.14062;,
 -0.14062;-0.80662;0.14062;,
 -0.14062;39.19822;0.14062;,
 -0.14062;-0.80662;-0.14062;,
 0.14062;-0.80662;-0.14062;,
 0.14062;-0.80662;0.14062;,
 -0.14062;-0.80662;0.14062;,
 0.14062;-0.80662;-0.14062;,
 0.14062;39.19822;-0.14062;,
 0.14062;39.19822;0.14062;,
 0.14062;-0.80662;0.14062;,
 -0.14062;39.19822;-0.14062;,
 0.14062;39.19822;-0.14062;,
 0.14062;39.19822;0.14062;,
 -0.14062;39.19822;0.14062;;
 
 48;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;9,10,11;,
 3;9,11,12;,
 3;9,12,13;,
 3;9,13,10;,
 3;14,15,16;,
 3;16,17,18;,
 3;18,19,20;,
 3;20,21,22;,
 3;23,24,25;,
 3;23,25,26;,
 3;23,26,27;,
 3;23,27,24;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;37,38,39;,
 3;37,39,40;,
 3;37,40,41;,
 3;37,41,38;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;54,47,58,59;,
 4;60,61,48,57;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;74,67,78,79;,
 4;80,81,68,77;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;94,87,98,99;,
 4;100,101,88,97;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;114,107,118,119;,
 4;120,121,108,117;;
 
 MeshMaterialList {
  5;
  48;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.000000;0.000000;0.950000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.700000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.800000;0.950000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.700000;;
  }
  Material {
   0.000000;0.599216;0.134902;0.950000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.524314;0.118039;;
  }
  Material {
   0.800000;0.800000;0.000000;0.950000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.700000;0.700000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;0.800000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  39;
  0.666667;0.333334;-0.666667;,
  0.666667;0.333334;0.666667;,
  -0.666667;0.333334;0.666667;,
  0.000000;-1.000000;-0.000000;,
  -0.666667;0.333334;-0.666667;,
  0.666667;-0.666667;-0.333334;,
  0.666667;0.666667;-0.333334;,
  -0.666667;0.666667;-0.333334;,
  0.000000;0.000000;1.000000;,
  -0.666667;-0.666667;-0.333334;,
  0.333334;-0.666667;0.666667;,
  0.333334;0.666667;0.666667;,
  0.333334;0.666667;-0.666667;,
  -1.000000;0.000000;0.000000;,
  0.333334;-0.666667;-0.666667;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;;
  48;
  3;0,0,0;,
  3;1,1,1;,
  3;2,2,2;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;5,5,5;,
  3;6,6,6;,
  3;7,7,7;,
  3;9,9,9;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;10,10,10;,
  3;11,11,11;,
  3;12,12,12;,
  3;14,14,14;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;;
 }
 MeshTextureCoords {
  122;
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}