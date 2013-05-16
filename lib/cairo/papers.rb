require 'cairo/paper'

module Cairo
  class Paper
    [
     [841, 1189, "A0"],
     [594, 841, "A1"],
     [420, 594, "A2"],
     [297, 420, "A3"],
     [210, 297, "A4"],
     [148, 210, "A5"],
     [105, 148, "A6"],
     [74, 105, "A7"],
     [52, 74, "A8"],
     [37, 52, "A9"],
     [26, 37, "A10"],

     [1000, 1414 , "ISO_B0"],
     [707, 1000 , "ISO_B1"],
     [500, 707 , "ISO_B2"],
     [353, 500 , "ISO_B3"],
     [250, 353 , "ISO_B4"],
     [176, 250 , "ISO_B5"],
     [125, 176 , "ISO_B6"],
     [88, 125 , "ISO_B7"],
     [62, 88 , "ISO_B8"],
     [44, 62 , "ISO_B9"],
     [31, 44 , "ISO_B10"],

     [1030, 1456, "JIS_B0"],
     [728, 1030, "JIS_B1"],
     [515, 728, "JIS_B2"],
     [364, 515, "JIS_B3"],
     [257, 364, "JIS_B4"],
     [182, 257, "JIS_B5"],
     [128, 182, "JIS_B6"],
     [91, 128, "JIS_B7"],
     [64, 91, "JIS_B8"],
     [45, 64, "JIS_B9"],
     [32, 45, "JIS_B10"],

     [1030, 1456, "B0"],
     [728, 1030, "B1"],
     [515, 728, "B2"],
     [364, 515, "B3"],
     [257, 364, "B4"],
     [182, 257, "B5"],
     [128, 182, "B6"],
     [91, 128, "B7"],
     [64, 91, "B8"],
     [45, 64, "B9"],
     [32, 45, "B10"],

     [215.9, 279.4, "letter"],
     [215.9, 355.6, "legal"],
     [279.9, 431.8, "tabloid"],
     [100, 148, "Japanese postcard"],
    ].each do |width, height, name|
      constant_name = name.upcase.gsub(/ +/, '_')
      const_set(constant_name, new(width, height, "mm", name))
      const_set("#{constant_name}_LANDSCAPE",
                new(height, width, "mm", "#{name} (landscape)"))
    end
  end
end
