struct ViewportClass
{
   HP Flt  from, range;
   HP Vec2 center, size, size_fov_tan;
   HP Vec4 FracToPosXY, ScreenToPosXY, PosToScreen;
};
PAR ViewportClass Viewport;

PAR HP Vec4 ImgClamp;
HP Vec2 UVClamp(HP Vec2 screen, const Bool do_clamp) {return do_clamp ? Mid(screen, ImgClamp.xy, ImgClamp.zw) : screen;}

PAR MP Vec4 Color[2];
