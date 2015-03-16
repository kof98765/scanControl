///////////////////////////////////////////////////////////////////////////////
//  File generated by HDevelop for HALCON/C++ Version 10.0
///////////////////////////////////////////////////////////////////////////////



#include "HalconCpp.h"



using namespace Halcon;

// Default exception handler 
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
  throw except;
}

// Procedure declarations 
// Chapter: Graphics / Text
// Short Description: This procedure writes a text message.
void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
    Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box);
// Local procedures 
// Chapter: Graphics, Window
// Short Description: Interactive display of a height field
void interactive_3d_plot (Halcon::Hobject HeightField, Halcon::HTuple WindowHandle, 
    Halcon::HTuple Mode, Halcon::HTuple ParamNames, Halcon::HTuple ParamValues);

// Procedures 
// Chapter: Graphics / Text
// Short Description: This procedure writes a text message.
void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
    Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box)
{
  using namespace Halcon;

  // Local control variables 
  HTuple  Red, Green, Blue, Row1Part, Column1Part;
  HTuple  Row2Part, Column2Part, RowWin, ColumnWin, WidthWin;
  HTuple  HeightWin, MaxAscent, MaxDescent, MaxWidth, MaxHeight;
  HTuple  R1, C1, FactorRow, FactorColumn, Width, Index, Ascent;
  HTuple  Descent, W, H, FrameHeight, FrameWidth, R2, C2;
  HTuple  DrawMode, Exception, CurrentColor;


  // Install default exception handler 
  HException::InstallHHandler(&CPPExpDefaultExceptionHandler);

  //This procedure displays text in a graphics window.
  //
  //Input parameters:
  //WindowHandle: The WindowHandle of the graphics window, where
  //   the message should be displayed
  //String: A tuple of strings containing the text message to be displayed
  //CoordSystem: If set to 'window', the text position is given
  //   with respect to the window coordinate system.
  //   If set to 'image', image coordinates are used.
  //   (This may be useful in zoomed images.)
  //Row: The row coordinate of the desired text position
  //   If set to -1, a default value of 12 is used.
  //Column: The column coordinate of the desired text position
  //   If set to -1, a default value of 12 is used.
  //Color: defines the color of the text as string.
  //   If set to [], '' or 'auto' the currently set color is used.
  //   If a tuple of strings is passed, the colors are used cyclically
  //   for each new textline.
  //Box: If set to 'true', the text is written within a white box.
  //
  //prepare window
  get_rgb(WindowHandle, &Red, &Green, &Blue);
  get_part(WindowHandle, &Row1Part, &Column1Part, &Row2Part, &Column2Part);
  get_window_extents(WindowHandle, &RowWin, &ColumnWin, &WidthWin, &HeightWin);
  set_part(WindowHandle, 0, 0, HeightWin-1, WidthWin-1);
  //
  //default settings
  if (0 != (Row==-1))
  {
    Row = 12;
  }
  if (0 != (Column==-1))
  {
    Column = 12;
  }
  if (0 != (Color==HTuple()))
  {
    Color = "";
  }
  //
  String = ((""+String)+"").Split("\n");
  //
  //Estimate extentions of text depending on font size.
  get_font_extents(WindowHandle, &MaxAscent, &MaxDescent, &MaxWidth, &MaxHeight);
  if (0 != (CoordSystem==HTuple("window")))
  {
    R1 = Row;
    C1 = Column;
  }
  else
  {
    //transform image to window coordinates
    FactorRow = (1.0*HeightWin)/((Row2Part-Row1Part)+1);
    FactorColumn = (1.0*WidthWin)/((Column2Part-Column1Part)+1);
    R1 = ((Row-Row1Part)+0.5)*FactorRow;
    C1 = ((Column-Column1Part)+0.5)*FactorColumn;
  }
  //
  //display text box depending on text size
  if (0 != (Box==HTuple("true")))
  {
    //calculate box extents
    String = (" "+String)+" ";
    Width = HTuple();
    for (Index=0; Index<=(String.Num())-1; Index+=1)
    {
      get_string_extents(WindowHandle, HTuple(String[Index]), &Ascent, &Descent, 
          &W, &H);
      Width.Append(W);
    }
    FrameHeight = MaxHeight*(String.Num());
    FrameWidth = (HTuple(0).Concat(Width)).Max();
    R2 = R1+FrameHeight;
    C2 = C1+FrameWidth;
    //display rectangles
    get_draw(WindowHandle, &DrawMode);
    set_draw(WindowHandle, "fill");
    set_color(WindowHandle, "light gray");
    disp_rectangle1(WindowHandle, R1+3, C1+3, R2+3, C2+3);
    set_color(WindowHandle, "white");
    disp_rectangle1(WindowHandle, R1, C1, R2, C2);
    set_draw(WindowHandle, DrawMode);
  }
  else if (0 != (Box!=HTuple("false")))
  {
    Exception = "Wrong value of control parameter Box";
    throw HException(Exception);
  }
  //Write text.
  for (Index=0; Index<=(String.Num())-1; Index+=1)
  {
    CurrentColor = Color[Index%(Color.Num())];
    if (0 != (HTuple(CurrentColor!=HTuple("")).And(CurrentColor!=HTuple("auto"))))
    {
      set_color(WindowHandle, CurrentColor);
    }
    else
    {
      set_rgb(WindowHandle, Red, Green, Blue);
    }
    Row = R1+(MaxHeight*Index);
    set_tposition(WindowHandle, Row, C1);
    write_string(WindowHandle, HTuple(String[Index]));
  }
  //reset changed window settings
  set_rgb(WindowHandle, Red, Green, Blue);
  set_part(WindowHandle, Row1Part, Column1Part, Row2Part, Column2Part);
  return;
}

// Local procedures 
// Chapter: Graphics, Window
// Short Description: Interactive display of a height field
void interactive_3d_plot (Halcon::Hobject HeightField, Halcon::HTuple WindowHandle, 
    Halcon::HTuple Mode, Halcon::HTuple ParamNames, Halcon::HTuple ParamValues)
{
  using namespace Halcon;

  // Local control variables 
  HTuple  PreviousPlotMode, Indices, ShowCoordinates;
  HTuple  Step, Button, ButtonDown, Row, Column, ImageRow;
  HTuple  ImageColumn, Height, WindowRow, WindowColumn, WindowWidth;
  HTuple  WindowHeight, BackgroundColor, mode, lastRow, lastCol;

  //This procedure is used for the interactive display of a height field
  //and demonstrates the use of the operators update_window_pose and
  //unproject_coordinates.
  //The user manipulates the pose of the height field using the mouse.
  //If the mouse is moved while the left mouse button is pressed, the
  //height field is rotated using a virtual trackball model. If the mouse
  //is moved up and down while the right mouse button is pressed, the
  //camera zoomes in and out. If the mouse is moved while the left and
  //the right mouse button are pressed, the height field is moved.
  //Interactive display ends as soon as the middle mouse button is
  //pressed.
  //Using ParamNames and ParamValues the following parameters can be
  //passed:
  //  plot_quality       the quality of the 3d_plot (see set_window_param)
  //  display_grid       display a grid at height = 0
  //  angle_of_view      parameter of the camera (see set_window_param)
  //  show_coordinates   if true, image coordinates are shown using unproject_coordinates
  //  step               step size of the 3d plot
  // dev_set_preferences(...); only in hdevelop
  get_paint(WindowHandle, &PreviousPlotMode);
  tuple_find(ParamNames, "plot_quality", &Indices);
  if (0 != (HTuple(Indices==-1).Not()))
  {
    set_window_param(WindowHandle, "plot_quality", HTuple(ParamValues[HTuple(Indices[0])]));
  }
  tuple_find(ParamNames, "display_grid", &Indices);
  if (0 != (HTuple(Indices==-1).Not()))
  {
    set_window_param(WindowHandle, "display_grid", HTuple(ParamValues[HTuple(Indices[0])]));
  }
  tuple_find(ParamNames, "angle_of_view", &Indices);
  if (0 != (HTuple(Indices==-1).Not()))
  {
    set_window_param(WindowHandle, "angle_of_view", HTuple(ParamValues[HTuple(Indices[0])]));
  }
  ShowCoordinates = 0;
  tuple_find(ParamNames, "show_coordinates", &Indices);
  if (0 != (HTuple(Indices==-1).Not()))
  {
    ShowCoordinates = ParamValues[HTuple(Indices[0])];
  }
  Step = "*";
  tuple_find(ParamNames, "step", &Indices);
  if (0 != (HTuple(Indices==-1).Not()))
  {
    Step = ParamValues[HTuple(Indices[0])];
  }
  set_paint(WindowHandle, ((HTuple("3d_plot").Concat(Mode)).Concat(Step)).Concat("auto"));
  set_window_param(WindowHandle, "interactive_plot", "true");
  set_colored(WindowHandle, 12);
  Button = HTuple();
  ButtonDown = 0;
  while (0 != 1)
  {
    set_check("~give_error");
    get_mposition_sub_pix(WindowHandle, &Row, &Column, &Button);
    if (0 != ShowCoordinates)
    {
      unproject_coordinates(HeightField, WindowHandle, Row, Column, &ImageRow, &ImageColumn, 
          &Height);
      get_window_extents(WindowHandle, &WindowRow, &WindowColumn, &WindowWidth, &WindowHeight);
      get_window_param(WindowHandle, "background_color", &BackgroundColor);
      set_color(WindowHandle, BackgroundColor);
      disp_rectangle1(WindowHandle, 0, 0, 19, WindowWidth-1);
      if (0 != (BackgroundColor==HTuple("black")))
      {
        set_color(WindowHandle, "white");
      }
      else
      {
        set_color(WindowHandle, "black");
      }
      set_tposition(WindowHandle, 1, 10);
      write_string(WindowHandle, "ImageRow: "+ImageRow);
      write_string(WindowHandle, "   ImageColumn: "+ImageColumn);
      write_string(WindowHandle, "   Height: "+Height);
      //reset colors, because the axis are drawn in the first three colors
      set_colored(WindowHandle, 12);
    }
    set_check("give_error");
    if (0 != (Button==HTuple()))
    {
      Button = 0;
    }
    if (0 != (ButtonDown.And(Button==0)))
    {
      ButtonDown = 0;
    }
    if (0 != (HTuple(Button==0).Not()))
    {
      if (0 != ButtonDown)
      {
        if (0 != (Button==1))
        {
          mode = "rotate";
        }
        if (0 != (Button==4))
        {
          mode = "scale";
        }
        if (0 != (Button==5))
        {
          mode = "move";
        }
        update_window_pose(WindowHandle, lastRow, lastCol, Row, Column, mode);
      }
      else
      {
        if (0 != (Button==2))
        {
          break;
        }
        ButtonDown = 1;
      }
      lastCol = Column;
      lastRow = Row;
    }
    //disp_image can not be used because it discards all channels but
    //the first, hence the texture mode would not work.
    disp_obj(HeightField, WindowHandle);
  }
  set_window_param(WindowHandle, "interactive_plot", "false");
  set_paint(WindowHandle, PreviousPlotMode);
  return;
}

#ifndef NO_EXPORT_MAIN
// Main procedure 
void action()
{
  using namespace Halcon;

  // Local iconic variables 
  Hobject  Image, Image1, Depth, Confidence, DepthHighConf;
  Hobject  SharpImage, ImageScaleMax, DepthMean;


  // Local control variables 
  HTuple  Names, i, Width, Height, WindowHandle;
  HTuple  j, WindowHandle2, WindowHandle3, WindowHandle4;
  HTuple  ShowCoordinates, Mode;

  //This example demonstrates the usage of the new '3d_plot' mode
  //of the operator set_paint. The results of depth_from_focus
  //are displayed in 3d and the user can manipulate the camera
  //using the mouse.
  Names = HTuple();
  if (HDevWindowStack::IsOpen())
    close_window(HDevWindowStack::Pop());
  for (i=1; i<=10; i+=1)
  {
    Names.Append("dff/focus_"+(i.ToString(".2")));
  }
  read_image(&Image, Names);
  channels_to_image(Image, &Image);
  get_image_size(Image, &Width, &Height);
  set_window_attr("background_color","black");
  open_window(0,0,Width/2,Height/2,0,"","",&WindowHandle);
  HDevWindowStack::Push(WindowHandle);
  // dev_update_var(...); only in hdevelop
  for (j=1; j<=5; j+=1)
  {
    for (i=1; i<=10; i+=1)
    {
      access_channel(Image, &Image1, i);
    }
  }
  // stop(); only in hdevelop
  set_window_attr("background_color","black");
  open_window((Height/2)+70,0,Width/2,Height/2,0,"","",&WindowHandle2);
  HDevWindowStack::Push(WindowHandle2);
  depth_from_focus(Image, &Depth, &Confidence, "highpass", "next_maximum");
  mean_image(Depth, &DepthHighConf, 11, 11);
  select_grayvalues_from_channels(Image, DepthHighConf, &SharpImage);
  scale_image_max(DepthHighConf, &ImageScaleMax);
  mean_image(ImageScaleMax, &DepthMean, 51, 51);
  compose2(DepthMean, SharpImage, &DepthMean);
  if (HDevWindowStack::IsOpen())
    disp_obj(SharpImage, HDevWindowStack::GetActive());
  //Sharp image now constructed
  // stop(); only in hdevelop
  open_window(100, (Width/2)+30, Width, Height, 0, "visible", "", &WindowHandle3);
  set_window_attr("background_color","white");
  open_window(Height+50,(Width/2)+30,Width,100,0,"","",&WindowHandle4);
  HDevWindowStack::Push(WindowHandle4);
  HDevWindowStack::SetActive(WindowHandle4);
  if (HDevWindowStack::IsOpen())
    set_color(HDevWindowStack::GetActive(),"black");
  disp_message(WindowHandle4, "The mouse can be used to manipulate the 3D plot in the following ways:", 
      "window", 0, 0, "black", "false");
  disp_message(WindowHandle4, " - The height field is rotated if the mouse is moved while the left mouse button is pressed.", 
      "window", 20, 10, "black", "false");
  disp_message(WindowHandle4, " - The height field is zoomed if the mouse is moved while the right mouse button is pressed.", 
      "window", 40, 10, "black", "false");
  disp_message(WindowHandle4, " - The height field is moved if the mouse is moved while the left and the right mouse button are pressed.", 
      "window", 60, 10, "black", "false");
  disp_message(WindowHandle4, "The 3D plot can be ended by pressing the middle mouse button(this may be the mouse wheel).", 
      "window", 80, 0, "black", "false");
  //Set ShowCoordinates to true to display image coordinates
  ShowCoordinates = 0;
  //ShowCoordinates := true
  //Choose one of the following modes available for 3d plot
  //Mode := 'shaded'
  //Mode := 'contour_lines'
  //Mode := 'hidden_lines'
  Mode = "texture";
  interactive_3d_plot(DepthMean, WindowHandle3, Mode, (((HTuple("plot_quality").Append("show_coordinates")).Append("step")).Append("display_grid")), 
      (HTuple("best").Concat(ShowCoordinates)).Concat((HTuple(1).Append("false"))));
  if (HDevWindowStack::IsOpen())
    set_paint(HDevWindowStack::GetActive(),"default");
  //stop ()
  //3 dimensional reconstruction
  HDevWindowStack::SetActive(WindowHandle);
  if (HDevWindowStack::IsOpen())
    close_window(HDevWindowStack::Pop());
  HDevWindowStack::SetActive(WindowHandle2);
  if (HDevWindowStack::IsOpen())
    close_window(HDevWindowStack::Pop());
  HDevWindowStack::SetActive(WindowHandle4);
  if (HDevWindowStack::IsOpen())
    close_window(HDevWindowStack::Pop());
  close_window(WindowHandle3);
}


#ifndef NO_EXPORT_APP_MAIN
int main(int argc, char *argv[])
{
  using namespace Halcon;
  // Default settings used in HDevelop (can be omitted) 
  set_system("do_low_error","false");
  action();
  return 0;
}
#endif


#endif

