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
 26;
 5.27669;0.65877;-12.22104;,
 5.27669;-0.62955;-12.22104;,
 0.00278;-0.62955;-3.60271;,
 0.00278;0.65877;-3.60271;,
 18.13993;0.65877;-13.82894;,
 18.13993;-0.62955;-13.82894;,
 33.76874;0.65877;-13.70030;,
 33.76874;-0.62955;-13.70030;,
 45.02404;0.65877;-13.18573;,
 45.02404;-0.62955;-13.18573;,
 59.17360;0.65877;-7.71893;,
 59.17360;-0.62955;-7.71893;,
 69.81671;0.65877;1.05384;,
 69.81671;-0.62955;1.05384;,
 72.61559;0.65877;8.13377;,
 72.61559;-0.62955;8.13377;,
 67.34691;0.65877;16.69555;,
 67.34691;-0.62955;16.69555;,
 54.99820;0.65877;18.01266;,
 54.99820;-0.62955;18.01266;,
 47.25969;0.65877;16.03693;,
 47.25969;-0.62955;16.03693;,
 19.59860;0.65877;9.45097;,
 19.59860;-0.62955;9.45097;,
 -0.48861;0.65877;5.66403;,
 -0.48861;-0.62955;5.66403;;
 
 35;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;6,8,9,7;,
 4;10,11,9,8;,
 4;12,13,11,10;,
 4;14,15,13,12;,
 4;16,17,15,14;,
 4;18,19,17,16;,
 4;18,20,21,19;,
 4;21,20,22,23;,
 4;22,24,25,23;,
 4;24,3,2,25;,
 3;18,16,20;,
 3;16,14,20;,
 3;20,14,22;,
 3;22,14,24;,
 3;14,12,24;,
 3;24,12,3;,
 3;12,10,3;,
 3;3,10,0;,
 3;10,8,0;,
 3;0,8,4;,
 3;8,6,4;,
 3;19,21,17;,
 3;17,21,15;,
 3;21,23,15;,
 3;23,25,15;,
 3;15,25,13;,
 3;25,2,13;,
 3;13,2,11;,
 3;2,1,11;,
 3;11,1,9;,
 3;1,5,9;,
 3;5,7,9;;
 
 MeshMaterialList {
  9;
  35;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_skin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_wing.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_eyes.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_eyes.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_wing.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_wing.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy003\\enemy_wing.png";
   }
  }
  Material {
   0.160000;0.091200;0.075200;1.000000;;
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
  16;
  -0.955021;0.000000;-0.296538;,
  -0.542154;0.000000;-0.840279;,
  -0.058029;0.000000;-0.998315;,
  0.026955;0.000000;-0.999637;,
  0.205710;0.000000;-0.978613;,
  0.504694;0.000000;-0.863298;,
  0.808645;0.000000;-0.588297;,
  0.996167;0.000000;0.087476;,
  0.533475;0.000000;0.845815;,
  -0.071795;0.000000;0.997419;,
  -0.239506;0.000000;0.970895;,
  -0.208499;0.000000;0.978023;,
  -0.185261;0.000000;0.982689;,
  -0.998597;0.000000;-0.052953;,
  0.000000;1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;;
  35;
  4;1,1,0,0;,
  4;2,2,1,1;,
  4;3,3,2,2;,
  4;3,4,4,3;,
  4;5,5,4,4;,
  4;6,6,5,5;,
  4;7,7,6,6;,
  4;8,8,7,7;,
  4;9,9,8,8;,
  4;9,10,10,9;,
  4;10,10,11,11;,
  4;11,12,12,11;,
  4;13,0,0,13;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;;
 }
 MeshTextureCoords {
  26;
  0.187957;0.844729;,
  0.187957;0.845027;,
  0.134505;0.630676;,
  0.134505;0.630378;,
  0.318327;0.884721;,
  0.318327;0.885018;,
  0.476728;0.881521;,
  0.476728;0.881819;,
  0.590802;0.868724;,
  0.590802;0.869022;,
  0.734210;0.732755;,
  0.734210;0.733053;,
  0.842078;0.514564;,
  0.842078;0.514861;,
  0.870447;0.338475;,
  0.870447;0.338773;,
  0.817047;0.125532;,
  0.817047;0.125829;,
  0.691891;0.092771;,
  0.691891;0.093069;,
  0.613460;0.141912;,
  0.613460;0.142210;,
  0.333111;0.305715;,
  0.333111;0.306013;,
  0.129524;0.399902;,
  0.129524;0.400199;;
 }
}