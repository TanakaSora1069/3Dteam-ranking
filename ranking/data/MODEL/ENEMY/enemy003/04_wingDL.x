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
 -0.98577;0.74506;-4.52469;,
 -0.98577;-0.54322;-4.52469;,
 -7.99986;-0.54322;-11.79744;,
 -7.99986;0.74506;-11.79744;,
 -20.90622;-0.54322;-10.58334;,
 -20.90622;0.74506;-10.58334;,
 -36.13679;-0.54322;-7.07546;,
 -36.13679;0.74506;-7.07546;,
 -47.01400;-0.54322;-4.13733;,
 -47.01400;0.74506;-4.13733;,
 -59.64511;-0.54322;4.26220;,
 -59.64511;0.74506;4.26220;,
 -68.13732;-0.54322;15.13039;,
 -68.13732;0.74506;15.13039;,
 -69.33781;-0.54322;22.64830;,
 -69.33781;0.74506;22.64830;,
 -62.34099;-0.54322;29.86682;,
 -62.34099;0.74506;29.86682;,
 -49.99985;-0.54322;28.48033;,
 -49.99985;0.74506;28.48033;,
 -42.87230;-0.54322;24.87668;,
 -42.87230;0.74506;24.87668;,
 -17.29213;-0.54322;12.46042;,
 -17.29213;0.74506;12.46042;,
 1.49945;-0.54322;4.41604;,
 1.49945;0.74506;4.41604;;
 
 35;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;6,8,9,7;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;18,20,21,19;,
 4;22,23,21,20;,
 4;22,24,25,23;,
 4;24,1,0,25;,
 3;17,19,15;,
 3;19,21,15;,
 3;21,23,15;,
 3;15,23,13;,
 3;13,23,11;,
 3;23,25,11;,
 3;25,0,11;,
 3;11,0,9;,
 3;9,0,7;,
 3;0,3,7;,
 3;3,5,7;,
 3;16,14,18;,
 3;18,14,20;,
 3;20,14,22;,
 3;14,12,22;,
 3;12,10,22;,
 3;22,10,24;,
 3;24,10,1;,
 3;10,8,1;,
 3;8,6,1;,
 3;1,6,2;,
 3;6,4,2;;
 
 MeshMaterialList {
  9;
  35;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
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
  0.868212;0.000000;-0.496193;,
  0.347453;0.000000;-0.937697;,
  -0.159400;0.000000;-0.987214;,
  -0.242650;0.000000;-0.970114;,
  -0.412622;0.000000;-0.910903;,
  -0.679569;0.000000;-0.733611;,
  -0.916795;0.000000;-0.399358;,
  -0.953628;0.000000;0.300987;,
  -0.337780;0.000000;0.941225;,
  0.285948;0.000000;0.958245;,
  0.443949;0.000000;0.896052;,
  0.415220;0.000000;0.909721;,
  0.393541;0.000000;0.919307;,
  0.963471;0.000000;-0.267812;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  35;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,4,4,3;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,10,10,9;,
  4;11,11,10,10;,
  4;11,12,12,11;,
  4;13,0,0,13;,
  3;14,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,14,15;,
  3;16,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,16,17;;
 }
 MeshTextureCoords {
  26;
  0.029467;0.351100;,
  0.029467;0.351474;,
  0.068528;0.651848;,
  0.068528;0.651474;,
  0.220493;0.794467;,
  0.220493;0.794093;,
  0.411212;0.904464;,
  0.411212;0.904090;,
  0.549793;0.970857;,
  0.549793;0.970483;,
  0.738086;0.907829;,
  0.738086;0.907455;,
  0.893329;0.718770;,
  0.893329;0.718396;,
  0.948095;0.523991;,
  0.948095;0.523617;,
  0.908932;0.225375;,
  0.908932;0.225001;,
  0.762384;0.095342;,
  0.762384;0.094968;,
  0.662367;0.098992;,
  0.662367;0.098617;,
  0.306248;0.097557;,
  0.306248;0.097183;,
  0.050546;0.066252;,
  0.050546;0.065878;;
 }
}