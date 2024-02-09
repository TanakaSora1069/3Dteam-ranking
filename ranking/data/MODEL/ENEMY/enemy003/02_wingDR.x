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
 8.04370;0.66639;-11.76762;,
 8.04370;-0.62189;-11.76762;,
 1.02961;-0.62189;-4.49487;,
 1.02961;0.66639;-4.49487;,
 20.95006;0.66639;-10.55352;,
 20.95006;-0.62189;-10.55352;,
 36.18063;0.66639;-7.04564;,
 36.18063;-0.62189;-7.04564;,
 47.05783;0.66639;-4.10752;,
 47.05783;-0.62189;-4.10752;,
 59.68889;0.66639;4.29201;,
 59.68889;-0.62189;4.29201;,
 68.18110;0.66639;15.16020;,
 68.18110;-0.62189;15.16020;,
 69.38159;0.66639;22.67811;,
 69.38159;-0.62189;22.67811;,
 62.38479;0.66639;29.89664;,
 62.38479;-0.62189;29.89664;,
 50.04367;0.66639;28.51014;,
 50.04367;-0.62189;28.51014;,
 42.91614;0.66639;24.90649;,
 42.91614;-0.62189;24.90649;,
 17.33597;0.66639;12.49023;,
 17.33597;-0.62189;12.49023;,
 -1.45561;0.66639;4.44586;,
 -1.45561;-0.62189;4.44586;;
 
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
 3;16,14,18;,
 3;18,14,20;,
 3;20,14,22;,
 3;14,12,22;,
 3;12,10,22;,
 3;22,10,24;,
 3;24,10,3;,
 3;10,8,3;,
 3;8,6,3;,
 3;3,6,0;,
 3;6,4,0;,
 3;17,19,15;,
 3;19,21,15;,
 3;21,23,15;,
 3;15,23,13;,
 3;13,23,11;,
 3;23,25,11;,
 3;25,2,11;,
 3;11,2,9;,
 3;9,2,7;,
 3;2,1,7;,
 3;1,5,7;;
 
 MeshMaterialList {
  9;
  35;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
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
  18;
  -0.868212;0.000000;-0.496193;,
  -0.347453;0.000000;-0.937697;,
  0.159399;0.000000;-0.987214;,
  0.242649;0.000000;-0.970114;,
  0.412623;0.000000;-0.910902;,
  0.679570;0.000000;-0.733611;,
  0.916795;0.000000;-0.399358;,
  0.953628;0.000000;0.300987;,
  0.337781;0.000000;0.941225;,
  -0.285949;0.000000;0.958245;,
  -0.443949;0.000000;0.896052;,
  -0.415220;0.000000;0.909721;,
  -0.393541;0.000000;0.919307;,
  -0.963471;0.000000;-0.267812;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
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
  3;14,15,14;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,17,16;;
 }
 MeshTextureCoords {
  26;
  0.049109;0.630178;,
  0.049109;0.630508;,
  0.009122;0.365444;,
  0.009122;0.365115;,
  0.204203;0.755698;,
  0.204203;0.756027;,
  0.398816;0.852323;,
  0.398816;0.852653;,
  0.540220;0.910587;,
  0.540220;0.910916;,
  0.732278;0.854476;,
  0.732278;0.854806;,
  0.890562;0.687192;,
  0.890562;0.687521;,
  0.946341;0.515110;,
  0.946341;0.515440;,
  0.906250;0.251599;,
  0.906250;0.251928;,
  0.756689;0.137175;,
  0.756689;0.137504;,
  0.654658;0.140647;,
  0.654658;0.140977;,
  0.291362;0.140272;,
  0.291362;0.140601;,
  0.030494;0.113276;,
  0.030494;0.113605;;
 }
}
