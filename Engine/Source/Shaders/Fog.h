/******************************************************************************/
BUFFER(Fog)
   VecH4 FogColor_Density; // rgb=color, a=density
BUFFER_END

inline VecH FogColor  () {return FogColor_Density.rgb;}
inline Flt  FogDensity() {return FogColor_Density.a  ;}
/******************************************************************************/
