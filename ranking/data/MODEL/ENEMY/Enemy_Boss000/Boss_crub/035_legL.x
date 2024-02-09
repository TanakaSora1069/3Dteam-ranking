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
 136;
 -70.83274;25.15681;5.98384;,
 -74.05557;34.43442;5.98384;,
 -74.05557;34.43442;-4.39580;,
 -70.83274;25.15681;-4.39580;,
 -69.77420;43.27349;5.98384;,
 -69.77420;43.27349;-4.39580;,
 -60.49658;46.49632;5.98384;,
 -60.49658;46.49628;-4.39580;,
 5.84855;9.02973;6.17731;,
 5.84855;9.02973;-4.58927;,
 7.76706;3.50685;6.17731;,
 7.76706;3.50685;-4.58927;,
 5.21837;-1.75499;6.17731;,
 5.21835;-1.75499;-4.58927;,
 -0.30450;-3.67348;6.17731;,
 -0.30450;-3.67348;-4.58927;,
 -61.24509;33.68586;-4.39580;,
 -61.24509;33.68586;5.98384;,
 17.56970;-0.15711;0.74772;,
 17.29319;-2.28684;-7.39227;,
 13.62322;7.24530;-7.39204;,
 13.89980;9.37503;0.73608;,
 13.62322;7.24530;8.44498;,
 17.29319;-2.28684;8.44526;,
 -1.45074;26.54773;0.69652;,
 -1.72724;24.41796;8.44500;,
 -1.72724;24.41796;-7.39202;,
 -70.27112;51.03629;0.62222;,
 -70.27112;48.88869;8.44498;,
 -59.95828;54.21893;8.44500;,
 -59.95828;56.36650;0.64685;,
 -59.95828;54.21893;-7.39201;,
 -70.27112;48.88869;-7.39201;,
 -81.68473;37.88066;-7.39201;,
 -86.83364;36.11498;0.59498;,
 -81.68473;37.88066;8.44498;,
 -62.91307;39.73462;-7.39201;,
 -62.91307;41.88219;0.63979;,
 -62.91307;39.73462;8.44498;,
 12.49541;-3.24136;0.73663;,
 12.49541;-3.24136;-7.39204;,
 12.49541;-3.24136;8.44498;,
 -45.83913;57.42069;0.67191;,
 -45.78764;55.16236;8.44500;,
 -45.89252;55.22812;-7.39201;,
 -30.37672;21.19181;8.44498;,
 -30.42808;22.44358;0.68152;,
 -30.48157;21.25160;-7.39202;,
 -18.46487;14.40318;-7.39202;,
 -18.46487;35.63724;-7.39201;,
 -17.64492;35.12318;8.44500;,
 -17.64492;13.93589;8.44498;,
 -18.04680;37.63410;0.68241;,
 -18.04603;15.03426;0.69740;,
 -66.42036;19.00869;8.08102;,
 -75.47827;24.23822;8.08102;,
 -75.47827;24.23822;-6.09560;,
 -66.42036;19.00869;-6.09560;,
 -75.47827;34.69738;8.08102;,
 -75.47827;34.69738;-6.09560;,
 -66.42036;39.92692;8.08102;,
 -66.42036;39.92692;-6.09560;,
 -57.36250;34.69738;8.08102;,
 -57.36250;34.69738;-6.09560;,
 -57.36250;24.23822;8.08102;,
 -57.36250;24.23822;-6.09560;,
 -66.42036;29.46780;-6.09560;,
 -66.42036;29.46780;8.08102;,
 -56.00879;-26.35714;6.93733;,
 -63.07589;-33.17733;6.93733;,
 -63.07589;-33.17733;-4.93850;,
 -56.00879;-26.35714;-4.93850;,
 -72.89575;-33.00274;6.93733;,
 -72.89575;-33.00274;-4.93850;,
 -79.71607;-25.93562;6.93733;,
 -79.71607;-25.93562;-4.93850;,
 -71.21950;30.44704;7.15870;,
 -71.21950;30.44704;-5.15981;,
 -66.62818;34.06683;7.15870;,
 -66.62818;34.06683;-5.15981;,
 -60.82202;33.37960;7.15870;,
 -60.82202;33.37960;-5.15981;,
 -57.20251;28.78817;7.15870;,
 -57.20251;28.78817;-5.15981;,
 -67.77513;-21.23646;-4.93850;,
 -67.77513;-21.23646;6.93733;,
 -91.70196;38.45114;0.95315;,
 -91.16796;40.14641;-7.18688;,
 -89.47932;33.01195;-7.18660;,
 -90.01345;31.31668;0.94147;,
 -89.47932;33.01195;8.65036;,
 -91.16796;40.14641;8.65059;,
 -86.28660;20.07906;0.90191;,
 -86.25977;22.99100;8.65036;,
 -86.25977;22.99100;-7.18660;,
 -90.71275;-33.33096;0.82764;,
 -91.93682;-26.80506;8.65036;,
 -91.58617;-21.74319;13.26110;,
 -98.13550;-24.21530;0.92235;,
 -91.58617;-21.74319;-11.79721;,
 -91.93682;-26.80506;-7.18658;,
 -87.04458;41.33745;0.94208;,
 -87.04458;41.33745;-7.18660;,
 -87.04458;41.33745;8.65036;,
 -92.13553;-9.48420;0.87735;,
 -89.30947;-7.86132;8.65036;,
 -89.31453;-7.94525;-7.18660;,
 -71.80765;4.32901;8.65036;,
 -73.25476;-27.72432;13.26110;,
 -67.17342;-23.35237;0.91117;,
 -66.28485;6.41523;0.88694;,
 -73.25476;-27.72432;-11.79721;,
 -71.80780;4.24823;-7.18660;,
 -70.06302;20.35317;-7.18660;,
 -82.86633;5.13425;-7.18660;,
 -82.82678;5.79045;8.65036;,
 -70.06212;20.98490;8.65036;,
 -84.71944;4.28369;0.88781;,
 -64.81048;20.21959;0.90287;,
 -74.09473;-30.16315;-8.34577;,
 -57.90656;-26.13431;0.86652;,
 -73.94636;-30.25445;9.77896;,
 -81.30584;-34.81606;-7.16319;,
 -81.53267;-41.85245;0.82119;,
 -88.71909;-35.18160;0.82627;,
 -81.30515;-34.79546;-7.18658;,
 -81.29290;-34.81499;-7.18658;,
 -80.66365;-35.53956;8.65036;,
 -81.07905;-34.85480;8.65036;,
 -81.12124;-35.50623;7.92151;,
 -67.32203;-35.18323;0.86117;,
 -60.22087;-72.09035;0.80037;,
 -75.89058;-43.40828;-7.18658;,
 -74.72078;-34.78044;-7.94169;,
 -74.73208;-35.57037;9.32284;,
 -75.89058;-43.40828;8.65036;;
 
 174;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;3,2,16;,
 3;2,5,16;,
 3;5,7,16;,
 3;7,9,16;,
 3;9,11,16;,
 3;11,13,16;,
 3;13,15,16;,
 3;15,3,16;,
 3;1,0,17;,
 3;4,1,17;,
 3;6,4,17;,
 3;8,6,17;,
 3;10,8,17;,
 3;12,10,17;,
 3;14,12,17;,
 3;0,14,17;,
 4;18,19,20,21;,
 4;21,22,23,18;,
 4;24,25,22,21;,
 4;21,20,26,24;,
 4;27,28,29,30;,
 4;30,31,32,27;,
 4;27,32,33,34;,
 4;34,35,28,27;,
 4;34,33,36,37;,
 4;37,38,35,34;,
 4;39,40,19,18;,
 4;18,23,41,39;,
 4;42,30,29,43;,
 4;44,31,30,42;,
 4;45,38,37,46;,
 4;46,37,36,47;,
 4;48,47,44,49;,
 4;50,43,45,51;,
 4;50,25,24,52;,
 4;52,42,43,50;,
 4;52,24,26,49;,
 4;49,44,42,52;,
 4;53,39,41,51;,
 4;51,45,46,53;,
 4;48,40,39,53;,
 4;53,46,47,48;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,54,57,65;,
 3;57,56,66;,
 3;56,59,66;,
 3;59,61,66;,
 3;61,63,66;,
 3;63,65,66;,
 3;65,57,66;,
 3;55,54,67;,
 3;58,55,67;,
 3;60,58,67;,
 3;62,60,67;,
 3;64,62,67;,
 3;54,64,67;,
 3;47,36,44;,
 3;33,32,36;,
 3;36,32,44;,
 3;32,31,44;,
 3;45,43,38;,
 3;35,38,28;,
 3;38,43,28;,
 3;43,29,28;,
 3;40,48,19;,
 3;19,48,20;,
 3;20,48,26;,
 3;48,49,26;,
 3;41,23,51;,
 3;23,22,51;,
 3;22,25,51;,
 3;25,50,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,68,71,83;,
 3;71,70,84;,
 3;70,73,84;,
 3;73,75,84;,
 3;75,77,84;,
 3;77,79,84;,
 3;79,81,84;,
 3;81,83,84;,
 3;83,71,84;,
 3;69,68,85;,
 3;72,69,85;,
 3;74,72,85;,
 3;76,74,85;,
 3;78,76,85;,
 3;80,78,85;,
 3;82,80,85;,
 3;68,82,85;,
 4;86,87,88,89;,
 4;89,90,91,86;,
 4;92,93,90,89;,
 4;89,88,94,92;,
 4;95,96,97,98;,
 4;98,99,100,95;,
 4;101,102,87,86;,
 4;86,91,103,101;,
 4;104,98,97,105;,
 4;106,99,98,104;,
 4;107,108,109,110;,
 4;110,109,111,112;,
 4;113,112,106,114;,
 4;115,105,107,116;,
 4;115,93,92,117;,
 4;117,104,105,115;,
 4;117,92,94,114;,
 4;114,106,104,117;,
 4;118,101,103,116;,
 4;116,107,110,118;,
 4;113,102,101,118;,
 4;118,110,112,113;,
 4;119,111,109,120;,
 4;120,109,108,121;,
 3;122,123,124;,
 3;122,125,126;,
 3;127,128,129;,
 3;124,123,129;,
 4;130,131,132,133;,
 4;133,119,120,130;,
 4;134,135,131,130;,
 4;130,120,121,134;,
 3;133,132,126;,
 4;126,125,119,133;,
 3;127,135,134;,
 4;134,121,128,127;,
 3;114,94,113;,
 3;113,94,102;,
 3;94,88,102;,
 3;88,87,102;,
 3;115,116,93;,
 3;116,103,93;,
 3;93,103,90;,
 3;103,91,90;,
 3;125,100,119;,
 3;119,100,111;,
 3;111,100,112;,
 3;100,99,112;,
 3;99,106,112;,
 3;128,121,96;,
 3;121,108,96;,
 3;108,107,96;,
 3;96,107,97;,
 3;107,105,97;,
 3;124,95,122;,
 3;95,100,122;,
 3;100,125,122;,
 3;123,122,131;,
 3;131,122,132;,
 3;122,126,132;,
 3;127,129,135;,
 3;135,129,131;,
 3;129,123,131;,
 3;128,96,129;,
 3;96,95,129;,
 3;95,124,129;;
 
 MeshMaterialList {
  6;
  174;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.300800;0.395200;0.552000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\clubskin.jpg";
   }
  }
  Material {
   0.649600;0.524000;0.320000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.075200;0.476800;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.248000;0.248000;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\metal.jpg";
   }
  }
  Material {
   0.496000;0.496000;0.496000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\metal.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  191;
  -0.001434;0.000694;-0.999999;,
  -0.725840;-0.687864;0.000000;,
  -0.998297;0.058331;0.000000;,
  -0.664656;0.747150;-0.000001;,
  0.089750;0.995964;-0.000002;,
  0.767716;0.640790;-0.000001;,
  0.998297;-0.058335;-0.000000;,
  0.664654;-0.747152;-0.000000;,
  -0.026855;-0.999639;-0.000000;,
  -0.001434;0.000694;0.999999;,
  0.925952;0.356423;-0.124803;,
  0.842476;0.513364;-0.163374;,
  0.641156;0.736736;-0.214799;,
  -0.263439;0.931685;-0.250125;,
  -0.560479;0.795704;-0.229606;,
  -0.664545;0.712926;-0.223868;,
  -0.175117;-0.973587;0.146504;,
  -0.080355;-0.993308;0.082957;,
  0.925067;0.356239;0.131701;,
  0.841201;0.512764;0.171620;,
  0.640003;0.735241;0.223199;,
  -0.262234;0.929434;0.259589;,
  -0.560108;0.794419;0.234898;,
  -0.664064;0.711939;0.228389;,
  -0.174762;-0.972950;-0.151086;,
  -0.080327;-0.993003;-0.086559;,
  0.933216;0.359298;0.003478;,
  0.853902;0.520416;0.004180;,
  0.656517;0.754299;0.004316;,
  -0.271812;0.962338;0.004866;,
  -0.576045;0.817413;0.002724;,
  -0.681969;0.731377;0.002321;,
  -0.176909;-0.984224;-0.002323;,
  -0.080631;-0.996742;-0.001806;,
  0.262580;0.930533;-0.255266;,
  -0.499105;-0.854459;0.144205;,
  0.262943;0.927972;0.264062;,
  -0.498553;-0.853912;-0.149261;,
  0.272095;0.962259;0.004643;,
  -0.504287;-0.863532;-0.002554;,
  0.000000;0.000000;-1.000000;,
  -0.000006;-0.000007;-1.000000;,
  -0.000001;-0.000001;1.000000;,
  -0.000007;-0.000009;1.000000;,
  0.568446;0.822715;0.003047;,
  -0.504318;-0.863517;-0.001316;,
  0.000000;0.000000;-1.000000;,
  -0.499996;-0.866028;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.499997;0.866027;0.000000;,
  0.499999;0.866026;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000940;0.001056;-0.999999;,
  -0.001411;0.000082;-0.999999;,
  -0.003064;-0.000492;-0.999995;,
  -0.002809;-0.000014;-0.999996;,
  -0.001731;0.002213;-0.999996;,
  -0.001514;0.002709;-0.999995;,
  -0.000940;0.001056;0.999999;,
  -0.001412;0.000082;0.999999;,
  -0.003064;-0.000492;0.999995;,
  -0.002810;-0.000014;0.999996;,
  -0.001731;0.002213;0.999996;,
  -0.001514;0.002709;0.999995;,
  0.167860;-0.985810;-0.001486;,
  0.167074;-0.981034;0.098282;,
  0.166971;-0.980750;-0.101239;,
  0.358990;-0.927646;0.102954;,
  0.360991;-0.932565;-0.002846;,
  0.358941;-0.927019;-0.108614;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.000001;1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.552882;0.800272;0.232135;,
  0.553754;0.801367;-0.226203;,
  -0.502589;-0.860679;-0.081461;,
  -0.502802;-0.860800;0.078834;,
  0.499998;-0.866027;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;-0.000004;1.000000;,
  -0.000035;-0.000060;-1.000000;,
  -0.000015;-0.000017;-1.000000;,
  0.000002;0.000013;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  -0.000042;-0.000074;1.000000;,
  -0.000018;-0.000022;1.000000;,
  0.000003;0.000015;1.000000;,
  -0.000000;-0.000001;1.000000;,
  -0.000226;-0.002472;-0.999997;,
  0.924618;-0.380897;-0.000000;,
  0.366200;-0.930536;-0.000000;,
  -0.399043;-0.916932;0.000000;,
  -0.952629;-0.304135;0.000000;,
  -0.864637;0.502397;0.000000;,
  -0.271457;0.962451;0.000000;,
  0.488628;0.872492;0.000000;,
  0.941207;0.337830;0.000000;,
  -0.000227;-0.002472;0.999997;,
  -0.967102;-0.228803;-0.111185;,
  -0.956256;-0.268580;-0.115925;,
  -0.964578;-0.225611;-0.136706;,
  -0.750752;0.060668;-0.657792;,
  -0.428294;-0.485582;-0.762085;,
  0.321133;-0.050148;-0.945705;,
  0.814969;0.055747;-0.576817;,
  -0.404135;0.911910;0.071384;,
  -0.966370;-0.228817;0.117356;,
  -0.955476;-0.268660;0.122011;,
  -0.962562;-0.227941;0.146690;,
  -0.744350;0.057847;0.665279;,
  -0.422676;-0.482267;0.767309;,
  0.315879;-0.051803;0.947384;,
  0.805622;0.058692;0.589516;,
  -0.404212;0.911555;-0.075374;,
  -0.973110;-0.230319;0.003106;,
  -0.962704;-0.270541;0.003065;,
  -0.973393;-0.229088;0.005052;,
  -0.993282;-0.115570;0.005782;,
  -0.717039;-0.696999;0.006934;,
  0.694288;-0.019355;-0.719437;,
  -0.405266;0.914197;-0.002000;,
  -0.746327;0.405472;-0.527815;,
  0.833237;-0.194867;-0.517438;,
  -0.747106;0.403240;0.528423;,
  0.404335;-0.015862;0.914473;,
  -0.921574;0.388202;-0.000179;,
  0.841042;-0.043624;0.539208;,
  0.000000;0.000000;-1.000000;,
  0.228948;-0.024542;-0.973129;,
  0.000000;0.000000;1.000000;,
  0.224587;-0.023851;0.974162;,
  -0.986846;0.161658;0.001326;,
  0.936770;0.349945;0.000681;,
  -0.403309;-0.365428;-0.838930;,
  0.242419;-0.287600;-0.926563;,
  -0.398387;-0.357147;0.844828;,
  0.238098;-0.284314;0.928695;,
  -0.647816;-0.562308;-0.513949;,
  0.723287;-0.125282;-0.679088;,
  -0.494530;-0.310624;-0.811759;,
  0.311104;-0.144099;-0.939388;,
  -0.492942;-0.299025;0.817063;,
  0.306827;-0.144492;0.940733;,
  -0.566706;-0.610088;-0.553748;,
  0.682132;-0.190209;-0.706057;,
  -0.661021;-0.577013;-0.479696;,
  -0.656309;-0.569145;0.495310;,
  -0.000882;-0.002026;-0.999998;,
  0.000821;-0.002086;-0.999997;,
  0.002425;-0.004120;-0.999989;,
  0.001367;-0.004030;-0.999991;,
  -0.002449;-0.003740;-0.999990;,
  -0.003094;-0.003770;-0.999988;,
  -0.000882;-0.002026;0.999998;,
  0.000821;-0.002087;0.999997;,
  0.002425;-0.004121;0.999989;,
  0.001368;-0.004031;0.999991;,
  -0.002450;-0.003741;0.999990;,
  -0.003095;-0.003771;0.999988;,
  0.851062;-0.045439;-0.523096;,
  -0.158951;0.166801;-0.973094;,
  -0.971327;0.156295;0.179156;,
  -0.970874;0.161863;-0.176648;,
  0.733669;0.679454;-0.008473;,
  0.718104;0.670205;0.187489;,
  0.720820;0.662389;-0.204106;,
  0.715110;-0.124287;0.687874;,
  -0.558521;-0.602114;0.570538;,
  -0.638590;-0.555013;0.533070;,
  0.685771;-0.025589;0.727367;,
  0.674673;-0.194460;0.712041;,
  0.000025;-0.000007;-1.000000;,
  0.000037;-0.000011;-1.000000;,
  0.000074;-0.000022;-1.000000;,
  0.000020;-0.000006;1.000000;,
  0.000031;-0.000009;1.000000;,
  0.000061;-0.000018;1.000000;,
  -0.185694;-0.780618;-0.596786;,
  -0.230006;0.149092;-0.961701;,
  0.740404;-0.479937;-0.470598;,
  -0.186667;-0.776774;0.601480;,
  -0.230042;0.148729;0.961749;,
  0.741325;-0.479290;0.469807;,
  -0.832449;-0.554023;0.009355;,
  -0.794356;-0.499704;-0.345389;,
  -0.793102;-0.491846;0.359273;;
  174;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;53,46,0;,
  3;46,46,0;,
  3;46,54,0;,
  3;54,55,0;,
  3;55,56,0;,
  3;56,57,0;,
  3;57,58,0;,
  3;58,53,0;,
  3;52,59,9;,
  3;52,52,9;,
  3;60,52,9;,
  3;61,60,9;,
  3;62,61,9;,
  3;63,62,9;,
  3;64,63,9;,
  3;59,64,9;,
  4;26,10,11,27;,
  4;27,19,18,26;,
  4;28,20,19,27;,
  4;27,11,12,28;,
  4;30,22,21,29;,
  4;29,13,14,30;,
  4;30,14,15,31;,
  4;31,23,22,30;,
  4;65,66,16,32;,
  4;32,24,67,65;,
  4;33,17,68,69;,
  4;69,70,25,33;,
  4;38,29,21,36;,
  4;34,13,29,38;,
  4;37,24,32,39;,
  4;39,32,16,35;,
  4;41,71,72,40;,
  4;42,73,74,43;,
  4;75,20,28,44;,
  4;44,38,36,75;,
  4;44,28,12,76;,
  4;76,34,38,44;,
  4;45,33,25,77;,
  4;77,37,39,45;,
  4;78,17,33,45;,
  4;45,39,35,78;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;79,79,79,79;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;71,80,72;,
  3;46,46,80;,
  3;80,46,72;,
  3;46,81,72;,
  3;74,73,82;,
  3;52,82,83;,
  3;82,73,83;,
  3;73,84,83;,
  3;85,41,86;,
  3;86,41,87;,
  3;87,41,88;,
  3;41,40,88;,
  3;89,90,43;,
  3;90,91,43;,
  3;91,92,43;,
  3;92,42,43;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;101,94,94,101;,
  3;152,132,93;,
  3;132,132,93;,
  3;132,153,93;,
  3;153,154,93;,
  3;154,155,93;,
  3;155,156,93;,
  3;156,157,93;,
  3;157,152,93;,
  3;134,158,102;,
  3;134,134,102;,
  3;159,134,102;,
  3;160,159,102;,
  3;161,160,102;,
  3;162,161,102;,
  3;163,162,102;,
  3;158,163,102;,
  4;119,103,104,120;,
  4;120,112,111,119;,
  4;121,113,112,120;,
  4;120,104,105,121;,
  4;123,115,114,122;,
  4;122,106,107,123;,
  4;125,110,110,125;,
  4;125,118,118,125;,
  4;130,122,114,128;,
  4;126,106,122,130;,
  4;129,117,117,131;,
  4;164,109,109,127;,
  4;133,165,132,132;,
  4;134,134,129,135;,
  4;166,113,121,136;,
  4;136,130,128,166;,
  4;136,121,105,167;,
  4;167,126,130,136;,
  4;137,168,169,169;,
  4;135,129,131,137;,
  4;170,170,168,137;,
  4;137,164,127,133;,
  4;139,109,109,143;,
  4;171,117,117,141;,
  3;150,142,148;,
  3;150,138,144;,
  3;146,140,151;,
  3;172,173,151;,
  4;149,124,108,145;,
  4;145,139,143,149;,
  4;147,116,174,175;,
  4;175,171,141,147;,
  3;145,108,144;,
  4;144,138,139,145;,
  3;146,116,147;,
  4;147,141,140,146;,
  3;132,132,133;,
  3;133,132,176;,
  3;132,177,176;,
  3;177,178,176;,
  3;134,135,134;,
  3;135,179,134;,
  3;134,179,180;,
  3;179,181,180;,
  3;138,107,139;,
  3;139,107,182;,
  3;183,107,165;,
  3;184,184,127;,
  3;106,126,165;,
  3;140,141,115;,
  3;141,185,115;,
  3;186,129,115;,
  3;187,129,187;,
  3;129,128,114;,
  3;148,123,150;,
  3;123,107,150;,
  3;107,138,150;,
  3;142,150,188;,
  3;188,150,189;,
  3;150,144,189;,
  3;146,151,190;,
  3;190,151,188;,
  3;151,173,188;,
  3;140,115,151;,
  3;115,123,151;,
  3;123,172,151;;
 }
 MeshTextureCoords {
  136;
  0.751287;-3.385675;,
  0.751263;-3.747169;,
  0.761008;-3.747169;,
  0.761221;-3.385675;,
  0.751296;-4.091578;,
  0.761293;-4.091578;,
  0.751373;-4.217153;,
  0.761964;-4.217153;,
  0.752048;-2.757295;,
  0.771112;-2.757295;,
  0.752093;-2.542100;,
  0.771570;-2.542100;,
  0.752034;-2.337076;,
  0.770965;-2.337076;,
  0.751916;-2.262324;,
  0.769765;-2.262324;,
  0.761907;-3.718003;,
  0.751366;-3.718003;,
  0.763464;0.257209;,
  0.779737;0.264603;,
  0.778427;0.251996;,
  0.762881;0.245336;,
  0.747817;0.249459;,
  0.747713;0.261835;,
  0.760906;0.243108;,
  0.748163;0.246586;,
  0.773997;0.248391;,
  0.756447;0.293408;,
  0.748924;0.295924;,
  0.748852;0.279433;,
  0.756850;0.276984;,
  0.765057;0.280130;,
  0.764124;0.296521;,
  0.763216;0.320209;,
  0.755884;0.326164;,
  0.748993;0.319714;,
  0.764777;0.301362;,
  0.756729;0.298025;,
  0.748874;0.300714;,
  0.762662;0.273876;,
  0.778047;0.275832;,
  0.747846;0.273392;,
  0.757506;0.260669;,
  0.748737;0.263179;,
  0.766549;0.264070;,
  0.748582;0.292571;,
  0.758414;0.290846;,
  0.768561;0.293642;,
  0.770504;0.289818;,
  0.770504;0.256174;,
  0.748422;0.254450;,
  0.748422;0.288236;,
  0.759331;0.251680;,
  0.759310;0.287134;,
  0.749257;-3.146118;,
  0.749296;-3.349884;,
  0.762494;-3.349884;,
  0.763191;-3.146118;,
  0.749296;-3.757416;,
  0.762494;-3.757416;,
  0.749257;-3.961181;,
  0.763191;-3.961181;,
  0.749213;-3.757416;,
  0.763971;-3.757416;,
  0.749213;-3.349884;,
  0.763971;-3.349884;,
  0.763191;-3.553650;,
  0.749257;-3.553650;,
  0.701476;-1.015314;,
  0.703496;-0.749569;,
  0.714535;-0.749569;,
  0.712954;-1.015314;,
  0.706046;-0.756372;,
  0.716524;-0.756372;,
  0.707663;-1.031737;,
  0.717780;-1.031737;,
  0.705437;-3.228647;,
  0.716400;-3.228647;,
  0.704253;-3.369688;,
  0.715486;-3.369688;,
  0.702666;-3.342911;,
  0.714258;-3.342911;,
  0.701621;-3.164010;,
  0.713447;-3.164010;,
  0.715515;-1.214837;,
  0.704751;-1.214837;,
  0.715013;0.343279;,
  0.721531;0.339628;,
  0.721278;0.347749;,
  0.714717;0.351447;,
  0.708416;0.350099;,
  0.708773;0.342019;,
  0.714055;0.364396;,
  0.707719;0.361533;,
  0.720785;0.359236;,
  0.714936;0.447654;,
  0.708933;0.438157;,
  0.705245;0.430564;,
  0.716156;0.435462;,
  0.725377;0.428653;,
  0.721644;0.437080;,
  0.714166;0.336389;,
  0.720907;0.335192;,
  0.707891;0.337728;,
  0.715151;0.410787;,
  0.708380;0.407928;,
  0.721254;0.406464;,
  0.704287;0.380155;,
  0.700714;0.434126;,
  0.710027;0.422850;,
  0.709840;0.372059;,
  0.722775;0.431914;,
  0.718346;0.377879;,
  0.718024;0.351859;,
  0.720246;0.383140;,
  0.706950;0.384198;,
  0.703836;0.353765;,
  0.713768;0.386405;,
  0.709475;0.349557;,
  0.719797;0.436733;,
  0.707785;0.423905;,
  0.703862;0.438331;,
  0.719972;0.447120;,
  0.713200;0.459609;,
  0.714572;0.450143;,
  0.719992;0.447083;,
  0.719990;0.447113;,
  0.706452;0.449180;,
  0.706548;0.448140;,
  0.707163;0.449191;,
  0.710107;0.444150;,
  0.708441;0.513381;,
  0.719075;0.460741;,
  0.719544;0.445096;,
  0.704450;0.447695;,
  0.705311;0.461547;;
 }
}
