#!/usr/bin/env ruby

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

require 'cairo'

INCHES_PER_MM = (1.0/25.4) 

WIDTH  = 210    # millimeters are needed for a european to make 
HEIGHT = 297    # heads or tails of things,..

DPI    = 72     # this must be 72,. any other value,. and
                # the dimensions of the generated pdf is wrong

FILENAME = 'pdf-a4_grid.pdf'

def grid_5mm cr
  cr.save {
    cr.rgb_color  = 0.5, 0.5, 0.5
    cr.line_width = 0.1
    cr.stroke {
       cr.move_to(0, 0)
       (HEIGHT/5+1).times {
         cr.rel_line_to(WIDTH,  0)
         cr.rel_move_to(-WIDTH, 5)
       }
       cr.move_to(0, 0)
       (WIDTH/5).times {
         cr.rel_line_to(0, HEIGHT)
         cr.rel_move_to(5, -HEIGHT)
       }
    }
  }
end

def include_text cr, x, y, file
  cr.select_font "Mono", Cairo::FONT_WEIGHT_NORMAL,
                         Cairo::FONT_SLANT_NORMAL
  cr.scale_font 5
  cr.rgb_color = 0,0,0

  puts file
  File.open(file).each{
    |line|
    line.chomp!
    cr.move_to(x,y)
    cr.show_text line
    y = y+5

    if y>290 then
      cr.show_page
      grid_5mm cr
      y = 9
    end
  }
end

File.open(FILENAME, "wb") {
  |stream|
  cr = Cairo::Context.new

  cr.set_target_pdf(stream,
           WIDTH * INCHES_PER_MM, HEIGHT * INCHES_PER_MM,
           DPI, DPI)

  foo_factor = (96.0/72.0)  # the foo factor is 1.3333,. but I suspect
                            # the magic numbers on the left has
                            # something to do with it

  cr.scale(INCHES_PER_MM * DPI * foo_factor,
           INCHES_PER_MM * DPI * foo_factor)


  grid_5mm cr
           
  cr.select_font "Sans", Cairo::FONT_WEIGHT_NORMAL,
                         Cairo::FONT_SLANT_NORMAL
  cr.scale_font 8    
  cr.rgb_color = 1,0,0

  cr.move_to 10, 15   # move to a suitable spot
  cr.show_text "#Hmm,. still too many unknowns in unit handling"
 
  include_text cr, 10, 24, "pdf-a4_grid.rb"
  
  cr.show_page
  cr.target_surface.finish
}



__END__

It is possible to force things into behaving,. but it there is
amounts of juggling that should be unneeded that was neccesary
to make it work,


/OEyvind Kolaas aka pippin   (hmm,. the embedding of fonts,
doesn't seem to like UTF8,. it works when using cr.text_path
instead of cr.show_text though,..)
