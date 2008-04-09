require 'cairo/paper'

module Cairo
  class Paper
    A0 = new(841, 1189, "A0")
    A1 = new(594, 841, "A1")
    A2 = new(420, 594, "A2")
    A3 = new(297, 420, "A3")
    A4 = new(210, 297, "A4")
    A5 = new(148, 210, "A5")
    A6 = new(105, 148, "A6")
    A7 = new(74, 105, "A7")
    A8 = new(52, 74, "A8")
    A9 = new(37, 52, "A9")
    A10 = new(26, 37, "A10")

    B0 = new(1030, 1456, "B0")
    B1 = new(728, 1030, "B1")
    B2 = new(515, 728, "B2")
    B3 = new(364, 515, "B3")
    B4 = new(257, 364, "B4")
    B5 = new(182, 257, "B5")
    B6 = new(128, 182, "B6")
    B7 = new(91, 128, "B7")
    B8 = new(64, 91, "B8")
    B9 = new(45, 64, "B9")
    B10 = new(32, 45, "B10")

    LETTER = new(215.9, 279.4, "letter")
    LEGAL = new(215.9, 355.6, "legal")
    TABLOID = new(279.9, 431.8, "tabloid")
    JAPANESE_POSTCARD = new(100, 148, "Japanese postcard")
  end
end
