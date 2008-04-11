require 'cairo/paper'

module Cairo
  class Paper
    A0 = new(841, 1189, "mm", "A0")
    A1 = new(594, 841, "mm", "A1")
    A2 = new(420, 594, "mm", "A2")
    A3 = new(297, 420, "mm", "A3")
    A4 = new(210, 297, "mm", "A4")
    A5 = new(148, 210, "mm", "A5")
    A6 = new(105, 148, "mm", "A6")
    A7 = new(74, 105, "mm", "A7")
    A8 = new(52, 74, "mm", "A8")
    A9 = new(37, 52, "mm", "A9")
    A10 = new(26, 37, "mm", "A10")

    B0 = new(1030, 1456, "mm", "B0")
    B1 = new(728, 1030, "mm", "B1")
    B2 = new(515, 728, "mm", "B2")
    B3 = new(364, 515, "mm", "B3")
    B4 = new(257, 364, "mm", "B4")
    B5 = new(182, 257, "mm", "B5")
    B6 = new(128, 182, "mm", "B6")
    B7 = new(91, 128, "mm", "B7")
    B8 = new(64, 91, "mm", "B8")
    B9 = new(45, 64, "mm", "B9")
    B10 = new(32, 45, "mm", "B10")

    LETTER = new(215.9, 279.4, "mm", "letter")
    LEGAL = new(215.9, 355.6, "mm", "legal")
    TABLOID = new(279.9, 431.8, "mm", "tabloid")
    JAPANESE_POSTCARD = new(100, 148, "mm", "Japanese postcard")
  end
end
