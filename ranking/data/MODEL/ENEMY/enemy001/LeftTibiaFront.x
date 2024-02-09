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
 180;
 -0.13782;0.09488;-0.01292;,
 -0.03387;0.76604;-0.57173;,
 -0.13595;0.09173;-0.79973;,
 0.00730;1.04718;-0.01637;,
 -0.03653;0.77049;0.54099;,
 -0.13973;0.09805;0.77389;,
 -0.24178;-0.57622;0.54588;,
 -0.28293;-0.85741;-0.00946;,
 -0.23910;-0.58068;-0.56683;,
 0.09591;0.84308;-0.62495;,
 -0.01593;0.10429;-0.87475;,
 0.14104;1.15110;-0.01648;,
 0.09299;0.84795;0.59421;,
 -0.02006;0.11117;0.84940;,
 -0.13187;-0.62764;0.59959;,
 -0.17697;-0.93569;-0.00888;,
 -0.12894;-0.63251;-0.61958;,
 0.44561;0.93398;-0.66960;,
 0.32548;0.14049;-0.93791;,
 0.49405;1.26481;-0.01609;,
 0.44248;0.93922;0.63982;,
 0.32106;0.14792;0.91387;,
 0.20095;-0.64558;0.64557;,
 0.15251;-0.97643;-0.00794;,
 0.20410;-0.65082;-0.66383;,
 0.96201;1.02494;-0.69888;,
 0.83635;0.19490;-0.97955;,
 1.01267;1.37106;-0.01528;,
 0.95873;1.03044;0.67083;,
 0.83173;0.20269;0.95752;,
 0.70610;-0.62735;0.67686;,
 0.65538;-0.97343;-0.00674;,
 0.70937;-0.63285;-0.69285;,
 2.01471;1.21428;-0.87095;,
 1.94261;0.12260;-1.22371;,
 2.04287;1.66932;-0.01088;,
 2.01057;1.22115;0.85264;,
 1.93677;0.13234;1.21380;,
 1.86464;-0.95937;0.86102;,
 1.83650;-1.41439;0.00098;,
 1.86877;-0.96627;-0.86256;,
 4.53495;1.21319;-0.86490;,
 4.46283;0.12150;-1.21768;,
 4.56312;1.66824;-0.00485;,
 4.53085;1.22010;0.85868;,
 4.45698;0.13125;1.21983;,
 4.38491;-0.96044;0.86705;,
 4.35673;-1.41551;0.00699;,
 4.38903;-0.96736;-0.85653;,
 10.75519;1.21052;-0.85001;,
 10.68310;0.11885;-1.20280;,
 10.78336;1.66557;0.01004;,
 10.75106;1.21742;0.87355;,
 10.67727;0.12860;1.23471;,
 10.60514;-0.96312;0.88194;,
 10.57698;-1.41815;0.02190;,
 10.60928;-0.96999;-0.84163;,
 15.38572;1.20854;-0.83893;,
 15.31359;0.11684;-1.19170;,
 15.41386;1.66359;0.02112;,
 15.38158;1.21546;0.88466;,
 15.30778;0.12663;1.24580;,
 15.23567;-0.96507;0.89303;,
 15.20751;-1.42012;0.03298;,
 15.23979;-0.97197;-0.83055;,
 17.86697;1.19095;-0.81980;,
 17.79594;0.11585;-1.16720;,
 17.89466;1.63904;0.02716;,
 17.86290;1.19773;0.87753;,
 17.79019;0.12545;1.23319;,
 17.71918;-0.94959;0.88579;,
 17.69147;-1.39775;0.03883;,
 17.72325;-0.95638;-0.81154;,
 18.62042;1.14349;-0.78045;,
 18.55253;0.11573;-1.11257;,
 18.64693;1.57189;0.02922;,
 18.61655;1.14999;0.84217;,
 18.54704;0.12495;1.18217;,
 18.47918;-0.90282;0.85006;,
 18.45267;-1.33120;0.04039;,
 18.48304;-0.90933;-0.77257;,
 19.12121;1.07275;-0.72306;,
 19.05799;0.11584;-1.03227;,
 19.14591;1.47164;0.03083;,
 19.11759;1.07880;0.78773;,
 19.05289;0.12440;1.10429;,
 18.98968;-0.83251;0.79507;,
 18.96501;-1.23139;0.04121;,
 18.99331;-0.83857;-0.71570;,
 19.29303;0.98949;-0.65634;,
 19.23535;0.11616;-0.93857;,
 19.31555;1.35357;0.03171;,
 19.28972;0.99501;0.72251;,
 19.23067;0.12395;1.01143;,
 19.17300;-0.74938;0.72922;,
 19.15046;-1.11345;0.04120;,
 19.17630;-0.75490;-0.64963;,
 19.23302;0.12006;0.03644;,
 18.20805;0.24475;-0.13798;,
 17.98149;-0.17975;0.32807;,
 18.19146;0.27798;0.49586;,
 17.90425;-0.38877;-0.11272;,
 18.00496;-0.22674;-0.56832;,
 18.22465;0.21152;-0.77183;,
 18.43464;0.66928;-0.60404;,
 18.51191;0.87830;-0.16324;,
 18.41117;0.71627;0.29235;,
 18.04614;-0.22290;0.37508;,
 18.27620;0.27861;0.55891;,
 17.96150;-0.45195;-0.10791;,
 18.07185;-0.27440;-0.60710;,
 18.31256;0.20579;-0.83007;,
 18.54265;0.70730;-0.64624;,
 18.62725;0.93633;-0.16326;,
 18.51694;0.75879;0.33594;,
 18.27360;-0.26466;0.41968;,
 18.52071;0.27401;0.61714;,
 18.18267;-0.51068;-0.09904;,
 18.30122;-0.31996;-0.63517;,
 18.55977;0.19580;-0.87466;,
 18.80688;0.73443;-0.67721;,
 18.89779;0.98045;-0.15849;,
 18.77926;0.78973;0.37764;,
 18.62927;-0.29855;0.45515;,
 18.88776;0.26491;0.66170;,
 18.53418;-0.55590;-0.08747;,
 18.65817;-0.35640;-0.64829;,
 18.92863;0.18310;-0.89881;,
 19.18706;0.74650;-0.69226;,
 19.28219;1.00387;-0.14965;,
 19.15816;0.80435;0.41118;,
 19.05894;-0.31954;0.47606;,
 19.32147;0.25266;0.68580;,
 18.96240;-0.58084;-0.07494;,
 19.08829;-0.37828;-0.64444;,
 19.36297;0.16959;-0.89883;,
 19.62538;0.74169;-0.68909;,
 19.72197;1.00302;-0.13809;,
 19.59604;0.80044;0.43141;,
 24.30696;1.05798;0.40853;,
 24.27016;1.54027;0.56016;,
 24.33147;0.83962;-0.00882;,
 24.32937;1.01311;-0.44741;,
 24.30185;1.47681;-0.65032;,
 24.26504;1.95902;-0.49869;,
 24.24050;2.17732;-0.08133;,
 24.24263;2.00389;0.35725;,
 25.09438;1.49907;0.39949;,
 25.15578;1.97053;0.55155;,
 25.07813;1.28556;-0.01265;,
 25.11646;1.45488;-0.44342;,
 25.18699;1.90804;-0.64051;,
 25.24836;2.37944;-0.48844;,
 25.26464;2.59298;-0.07630;,
 25.22629;2.42363;0.35447;,
 25.39139;1.45439;0.39100;,
 25.45010;1.90516;0.53635;,
 25.37583;1.25024;-0.00300;,
 25.41249;1.41214;-0.41481;,
 25.47994;1.84542;-0.60322;,
 25.53860;2.29603;-0.45785;,
 25.55415;2.50019;-0.06386;,
 25.51749;2.33828;0.34796;,
 25.44407;1.37477;0.36868;,
 25.57276;1.77691;0.50689;,
 25.39892;1.19188;0.00067;,
 25.46371;1.33544;-0.38159;,
 25.60054;1.72128;-0.55414;,
 25.72920;2.12340;-0.41594;,
 25.77442;2.30625;-0.04792;,
 25.70957;2.16273;0.33433;,
 25.52217;1.41349;0.33583;,
 25.63972;1.78055;0.46197;,
 25.48102;1.24666;-0.00006;,
 25.54009;1.37759;-0.34894;,
 25.66506;1.72979;-0.50642;,
 25.78253;2.09683;-0.38030;,
 25.82372;2.26370;-0.04440;,
 25.76460;2.13273;0.30448;,
 25.65238;1.75517;-0.02223;;
 
 192;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,74,82,88;,
 4;82,81,89,90;,
 4;81,83,91,89;,
 4;83,84,92,91;,
 4;84,85,93,92;,
 4;85,86,94,93;,
 4;86,87,95,94;,
 4;87,88,96,95;,
 4;88,82,90,96;,
 3;90,89,97;,
 3;89,91,97;,
 3;91,92,97;,
 3;92,93,97;,
 3;93,94,97;,
 3;94,95,97;,
 3;95,96,97;,
 3;96,90,97;,
 3;98,99,100;,
 3;98,101,99;,
 3;98,102,101;,
 3;98,103,102;,
 3;98,104,103;,
 3;98,105,104;,
 3;98,106,105;,
 3;98,100,106;,
 4;100,99,107,108;,
 4;99,101,109,107;,
 4;101,102,110,109;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,106,114,113;,
 4;106,100,108,114;,
 4;108,107,115,116;,
 4;107,109,117,115;,
 4;109,110,118,117;,
 4;110,111,119,118;,
 4;111,112,120,119;,
 4;112,113,121,120;,
 4;113,114,122,121;,
 4;114,108,116,122;,
 4;116,115,123,124;,
 4;115,117,125,123;,
 4;117,118,126,125;,
 4;118,119,127,126;,
 4;119,120,128,127;,
 4;120,121,129,128;,
 4;121,122,130,129;,
 4;122,116,124,130;,
 4;124,123,131,132;,
 4;123,125,133,131;,
 4;125,126,134,133;,
 4;126,127,135,134;,
 4;127,128,136,135;,
 4;128,129,137,136;,
 4;129,130,138,137;,
 4;130,124,132,138;,
 4;132,131,139,140;,
 4;131,133,141,139;,
 4;133,134,142,141;,
 4;134,135,143,142;,
 4;135,136,144,143;,
 4;136,137,145,144;,
 4;137,138,146,145;,
 4;138,132,140,146;,
 4;140,139,147,148;,
 4;139,141,149,147;,
 4;141,142,150,149;,
 4;142,143,151,150;,
 4;143,144,152,151;,
 4;144,145,153,152;,
 4;145,146,154,153;,
 4;146,140,148,154;,
 4;148,147,155,156;,
 4;147,149,157,155;,
 4;149,150,158,157;,
 4;150,151,159,158;,
 4;151,152,160,159;,
 4;152,153,161,160;,
 4;153,154,162,161;,
 4;154,148,156,162;,
 4;156,155,163,164;,
 4;155,157,165,163;,
 4;157,158,166,165;,
 4;158,159,167,166;,
 4;159,160,168,167;,
 4;160,161,169,168;,
 4;161,162,170,169;,
 4;162,156,164,170;,
 4;164,163,171,172;,
 4;163,165,173,171;,
 4;165,166,174,173;,
 4;166,167,175,174;,
 4;167,168,176,175;,
 4;168,169,177,176;,
 4;169,170,178,177;,
 4;170,164,172,178;,
 3;172,171,179;,
 3;171,173,179;,
 3;173,174,179;,
 3;174,175,179;,
 3;175,176,179;,
 3;176,177,179;,
 3;177,178,179;,
 3;178,172,179;;
 
 MeshMaterialList {
  2;
  192;
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
   0.097270;0.097270;0.097270;1.000000;;
   11.000000;
   0.600000;0.600000;0.600000;;
   0.045210;0.045210;0.045210;;
  }
  Material {
   0.225920;0.000000;0.000000;1.000000;;
   41.000000;
   0.370000;0.370000;0.370000;;
   0.021180;0.000000;0.000000;;
  }
 }
 MeshNormals {
  198;
  -0.988583;0.150645;-0.002979;,
  -0.872627;0.125236;-0.472057;,
  -0.865306;0.390175;-0.314656;,
  -0.868199;0.496200;-0.004058;,
  -0.866789;0.392677;0.307378;,
  -0.874886;0.129015;0.466829;,
  -0.988586;0.150631;-0.003008;,
  -0.988586;0.150630;-0.002984;,
  -0.988586;0.150631;-0.002960;,
  -0.366886;0.044474;-0.929202;,
  -0.427422;0.618079;-0.659764;,
  -0.470021;0.882643;-0.004654;,
  -0.430560;0.623331;0.652746;,
  -0.371330;0.051914;0.927049;,
  -0.359383;-0.583141;0.728553;,
  -0.373389;-0.927671;0.002807;,
  -0.355870;-0.588968;-0.725584;,
  -0.133103;0.013034;-0.991016;,
  -0.209004;0.652549;-0.728353;,
  -0.254220;0.967136;-0.004486;,
  -0.212485;0.658354;0.722094;,
  -0.137826;0.020961;0.990235;,
  -0.081325;-0.646613;0.758470;,
  -0.058439;-0.998284;0.003858;,
  -0.077737;-0.652668;-0.753646;,
  -0.151082;0.012621;-0.988441;,
  -0.194872;0.649013;-0.735396;,
  -0.233182;0.972422;-0.004563;,
  -0.200394;0.654765;0.728783;,
  -0.158444;0.020794;0.987149;,
  -0.159961;-0.633238;0.757246;,
  -0.173646;-0.984802;0.003472;,
  -0.154426;-0.639576;-0.753057;,
  -0.109037;0.007345;-0.994011;,
  -0.116002;0.646672;-0.753896;,
  -0.134932;0.990845;-0.004396;,
  -0.121649;0.652680;0.747803;,
  -0.116439;0.015563;0.993076;,
  -0.149285;-0.629350;0.762648;,
  -0.177619;-0.984093;0.003458;,
  -0.143719;-0.635716;-0.758426;,
  0.002393;-0.003998;-0.999989;,
  0.002111;0.642881;-0.765963;,
  0.000439;0.999992;-0.004003;,
  -0.001544;0.648990;0.760796;,
  -0.002392;0.004004;0.999989;,
  -0.002110;-0.642879;0.765965;,
  -0.000440;-0.999992;0.004003;,
  0.001541;-0.648992;-0.760794;,
  0.002392;-0.004000;-0.999989;,
  0.002109;0.642881;-0.765963;,
  0.000437;0.999992;-0.004006;,
  -0.001544;0.648990;0.760795;,
  -0.002392;0.004006;0.999989;,
  -0.002107;-0.642877;0.765967;,
  -0.000435;-0.999992;0.003997;,
  0.001545;-0.648991;-0.760795;,
  0.006130;-0.004233;-0.999972;,
  0.006287;0.642737;-0.766061;,
  0.005168;0.999979;-0.003994;,
  0.002636;0.648849;0.760913;,
  0.001345;0.003777;0.999992;,
  0.002065;-0.643005;0.765860;,
  0.004285;-0.999983;0.004009;,
  0.005718;-0.649118;-0.760666;,
  0.040967;-0.006340;-0.999140;,
  0.045350;0.640791;-0.766375;,
  0.049457;0.998769;-0.003880;,
  0.041693;0.646907;0.761429;,
  0.036190;0.001665;0.999344;,
  0.040870;-0.643625;0.764249;,
  0.048098;-0.998834;0.004113;,
  0.044505;-0.649725;-0.758865;,
  0.114575;-0.010775;-0.993356;,
  0.128034;0.633206;-0.763320;,
  0.143230;0.989683;-0.003619;,
  0.124390;0.639300;0.758830;,
  0.109828;-0.002817;0.993947;,
  0.122296;-0.641602;0.757225;,
  0.139451;-0.990220;0.004302;,
  0.125894;-0.647648;-0.751467;,
  0.316954;-0.023141;-0.948159;,
  0.353663;0.586709;-0.728489;,
  0.394994;0.918680;-0.002731;,
  0.350203;0.592524;0.725447;,
  0.312425;-0.015548;0.949815;,
  0.338005;-0.613367;0.713816;,
  0.373242;-0.927722;0.004620;,
  0.341427;-0.619057;-0.707246;,
  0.466994;-0.032249;-0.883672;,
  0.517270;0.527628;-0.673826;,
  0.912317;0.409485;0.000552;,
  0.514078;0.533002;0.672036;,
  0.462776;-0.025173;0.886118;,
  0.860191;-0.355653;0.365489;,
  0.870432;-0.492273;0.004064;,
  0.861935;-0.358544;-0.358489;,
  0.997766;-0.066756;0.002660;,
  -0.901433;0.430449;-0.046167;,
  -0.832774;0.513516;0.206855;,
  -0.901441;0.430434;-0.046165;,
  -0.901440;0.430436;-0.046166;,
  -0.901440;0.430435;-0.046169;,
  -0.819419;0.486816;-0.302594;,
  -0.735220;0.598737;-0.317752;,
  -0.717810;0.694049;-0.055181;,
  -0.749178;0.626636;0.214616;,
  -0.412219;0.214195;0.885548;,
  -0.492832;-0.479358;0.726177;,
  -0.522307;-0.852194;0.031000;,
  -0.455533;-0.553979;-0.696848;,
  -0.364799;0.119335;-0.923407;,
  -0.313971;0.704347;-0.636646;,
  -0.309761;0.949052;-0.057867;,
  -0.344867;0.766156;0.542284;,
  -0.172869;0.112658;0.978481;,
  -0.197825;-0.620528;0.758822;,
  -0.193726;-0.979962;0.046301;,
  -0.159652;-0.696959;-0.699114;,
  -0.121259;0.009326;-0.992577;,
  -0.102444;0.691321;-0.715249;,
  -0.109924;0.992422;-0.054908;,
  -0.137739;0.761992;0.632769;,
  -0.085773;0.076899;0.993343;,
  -0.102533;-0.649857;0.753109;,
  -0.094296;-0.994305;0.049656;,
  -0.064860;-0.725271;-0.685402;,
  -0.033593;-0.027557;-0.999056;,
  -0.018972;0.677883;-0.734925;,
  -0.028184;0.998193;-0.053071;,
  -0.055453;0.750915;0.658066;,
  -0.022988;0.055664;0.998185;,
  0.057703;-0.662650;0.746703;,
  0.102083;-0.993268;0.054746;,
  0.094779;-0.736882;-0.669345;,
  0.029287;-0.049004;-0.998369;,
  -0.064938;0.665616;-0.743464;,
  -0.122621;0.990919;-0.055160;,
  -0.101827;0.739481;0.665431;,
  0.001505;0.050282;0.998734;,
  0.261625;-0.625465;0.735082;,
  0.384055;-0.921464;0.058366;,
  0.297920;-0.698131;-0.651043;,
  0.053766;-0.054348;-0.997073;,
  -0.199183;0.636081;-0.745471;,
  -0.314811;0.947386;-0.057908;,
  -0.236078;0.709948;0.663507;,
  0.027977;0.046080;0.998546;,
  0.135129;-0.629347;0.765286;,
  0.205703;-0.976976;0.056604;,
  0.173167;-0.705500;-0.687228;,
  0.080188;-0.058438;-0.995065;,
  -0.000371;0.632057;-0.774922;,
  -0.042809;0.997654;-0.053423;,
  -0.039093;0.709562;0.703558;,
  0.119722;0.013212;0.992720;,
  -0.299411;-0.562826;0.770441;,
  -0.557538;-0.829648;0.028902;,
  -0.260339;-0.641069;-0.721979;,
  0.171429;-0.090266;-0.981053;,
  0.427952;0.538744;-0.725681;,
  0.509418;0.859933;-0.031749;,
  0.390944;0.612796;0.686763;,
  0.379870;-0.073682;0.922101;,
  0.361298;-0.558248;0.746876;,
  -0.862479;-0.506077;0.003962;,
  -0.813387;-0.497892;-0.300840;,
  0.427265;-0.168582;-0.888271;,
  0.612584;0.430575;-0.662832;,
  0.668987;0.742964;-0.021446;,
  0.578369;0.499128;0.645260;,
  0.845491;-0.251951;0.470814;,
  0.804544;-0.503704;0.314628;,
  0.797321;-0.601277;0.052390;,
  0.818478;-0.531623;-0.217876;,
  0.868202;-0.297452;-0.397174;,
  0.639441;0.409454;-0.650740;,
  0.653755;0.756370;-0.022552;,
  0.605827;0.476888;0.636830;,
  0.947362;-0.317471;0.041443;,
  -0.557526;-0.498928;0.663503;,
  -0.594247;-0.804281;0.001777;,
  -0.554257;-0.504276;-0.662197;,
  0.997766;-0.066755;0.002647;,
  0.997766;-0.066751;0.002653;,
  0.997766;-0.066748;0.002671;,
  0.997766;-0.066749;0.002674;,
  -0.596773;-0.020286;0.802154;,
  -0.689300;-0.329949;0.644981;,
  -0.741506;-0.670762;0.015750;,
  -0.655520;-0.397488;-0.642103;,
  -0.554019;-0.105723;-0.825764;,
  -0.829306;-0.465993;0.308386;,
  0.398232;-0.632244;-0.664589;,
  0.554275;-0.830308;0.058030;,
  0.947377;-0.317421;0.041482;,
  0.947387;-0.317395;0.041449;,
  0.947383;-0.317413;0.041403;;
  192;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,180,14,13;,
  4;180,181,15,14;,
  4;181,182,16,15;,
  4;182,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,81,89,96;,
  3;183,184,97;,
  3;184,91,97;,
  3;91,185,97;,
  3;185,186,97;,
  3;186,94,97;,
  3;94,95,97;,
  3;95,96,97;,
  3;96,183,97;,
  3;98,100,99;,
  3;98,101,100;,
  3;98,102,101;,
  3;98,103,102;,
  3;98,104,103;,
  3;98,105,104;,
  3;98,106,105;,
  3;98,99,106;,
  4;187,188,108,107;,
  4;188,189,109,108;,
  4;189,190,110,109;,
  4;190,191,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,99,107,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,114,122,121;,
  4;114,107,115,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,121,129,128;,
  4;121,122,130,129;,
  4;122,115,123,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,129,137,136;,
  4;129,130,138,137;,
  4;130,123,131,138;,
  4;131,132,140,139;,
  4;132,133,141,140;,
  4;133,134,142,141;,
  4;134,135,143,142;,
  4;135,136,144,143;,
  4;136,137,145,144;,
  4;137,138,146,145;,
  4;138,131,139,146;,
  4;139,140,148,147;,
  4;140,141,149,148;,
  4;141,142,150,149;,
  4;142,143,151,150;,
  4;143,144,152,151;,
  4;144,145,153,152;,
  4;145,146,154,153;,
  4;146,139,147,154;,
  4;147,148,156,155;,
  4;148,149,157,156;,
  4;149,150,158,157;,
  4;150,151,159,158;,
  4;151,152,160,159;,
  4;152,153,161,160;,
  4;153,154,162,161;,
  4;154,147,155,162;,
  4;155,156,164,163;,
  4;156,157,165,192;,
  4;157,158,166,165;,
  4;158,159,167,193;,
  4;159,160,168,167;,
  4;160,161,169,168;,
  4;161,162,170,169;,
  4;162,155,163,170;,
  4;163,164,172,171;,
  4;164,194,173,172;,
  4;194,193,174,173;,
  4;193,167,175,174;,
  4;167,168,176,175;,
  4;168,169,177,176;,
  4;169,170,178,177;,
  4;170,163,171,178;,
  3;171,172,179;,
  3;172,173,179;,
  3;173,174,179;,
  3;174,175,179;,
  3;175,195,179;,
  3;195,196,179;,
  3;196,197,179;,
  3;197,171,179;;
 }
 MeshTextureCoords {
  180;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
