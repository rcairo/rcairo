class ColorsTest < Test::Unit::TestCase
  # Absolute Zero: #0048BA: (0, 72, 186)
  test("Absolute Zero") do
    assert_equal("\#%02X%02X%02XFF" % [0, 72, 186],
                 Cairo::Color::ABSOLUTE_ZERO.to_s)
  end

  # Acid green: #B0BF1A: (176, 191, 26)
  test("Acid green") do
    assert_equal("\#%02X%02X%02XFF" % [176, 191, 26],
                 Cairo::Color::ACID_GREEN.to_s)
  end

  # Aero: #7CB9E8: (124, 185, 232)
  test("Aero") do
    assert_equal("\#%02X%02X%02XFF" % [124, 185, 232],
                 Cairo::Color::AERO.to_s)
  end

  # Aero blue: #C9FFE5: (201, 255, 229)
  test("Aero blue") do
    assert_equal("\#%02X%02X%02XFF" % [201, 255, 229],
                 Cairo::Color::AERO_BLUE.to_s)
  end

  # African violet: #B284BE: (178, 132, 190)
  test("African violet") do
    assert_equal("\#%02X%02X%02XFF" % [178, 132, 190],
                 Cairo::Color::AFRICAN_VIOLET.to_s)
  end

  # Alabama crimson: #AF002A: (175, 0, 42)
  test("Alabama crimson") do
    assert_equal("\#%02X%02X%02XFF" % [175, 0, 42],
                 Cairo::Color::ALABAMA_CRIMSON.to_s)
  end

  # Alabaster: #F2F0E6: (242, 240, 230)
  test("Alabaster") do
    assert_equal("\#%02X%02X%02XFF" % [242, 240, 230],
                 Cairo::Color::ALABASTER.to_s)
  end

  # Alice blue: #F0F8FF: (240, 248, 255)
  test("Alice blue") do
    assert_equal("\#%02X%02X%02XFF" % [240, 248, 255],
                 Cairo::Color::ALICE_BLUE.to_s)
  end

  # Alien Armpit: #84DE02: (132, 222, 2)
  test("Alien Armpit") do
    assert_equal("\#%02X%02X%02XFF" % [132, 222, 2],
                 Cairo::Color::ALIEN_ARMPIT.to_s)
  end

  # Alloy orange: #C46210: (196, 98, 16)
  test("Alloy orange") do
    assert_equal("\#%02X%02X%02XFF" % [196, 98, 16],
                 Cairo::Color::ALLOY_ORANGE.to_s)
  end

  # Almond: #EFDECD: (239, 222, 205)
  test("Almond") do
    assert_equal("\#%02X%02X%02XFF" % [239, 222, 205],
                 Cairo::Color::ALMOND.to_s)
  end

  # Amaranth: #E52B50: (229, 43, 80)
  test("Amaranth") do
    assert_equal("\#%02X%02X%02XFF" % [229, 43, 80],
                 Cairo::Color::AMARANTH.to_s)
  end

  # Amaranth deep purple: #9F2B68: (159, 43, 104)
  test("Amaranth deep purple") do
    assert_equal("\#%02X%02X%02XFF" % [159, 43, 104],
                 Cairo::Color::AMARANTH_DEEP_PURPLE.to_s)
  end

  # Amaranth pink: #F19CBB: (241, 156, 187)
  test("Amaranth pink") do
    assert_equal("\#%02X%02X%02XFF" % [241, 156, 187],
                 Cairo::Color::AMARANTH_PINK.to_s)
  end

  # Amaranth purple: #AB274F: (171, 39, 79)
  test("Amaranth purple") do
    assert_equal("\#%02X%02X%02XFF" % [171, 39, 79],
                 Cairo::Color::AMARANTH_PURPLE.to_s)
  end

  # Amaranth red: #D3212D: (211, 33, 45)
  test("Amaranth red") do
    assert_equal("\#%02X%02X%02XFF" % [211, 33, 45],
                 Cairo::Color::AMARANTH_RED.to_s)
  end

  # Amazon: #3B7A57: (59, 122, 87)
  test("Amazon") do
    assert_equal("\#%02X%02X%02XFF" % [59, 122, 87],
                 Cairo::Color::AMAZON.to_s)
  end

  # Amber: #FFBF00: (255, 191, 0)
  test("Amber") do
    assert_equal("\#%02X%02X%02XFF" % [255, 191, 0],
                 Cairo::Color::AMBER.to_s)
  end

  # Amber (SAE/ECE): #FF7E00: (255, 126, 0)
  test("Amber (SAE/ECE)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 126, 0],
                 Cairo::Color::AMBER_SAE_ECE.to_s)
  end

  # Amethyst: #9966CC: (153, 102, 204)
  test("Amethyst") do
    assert_equal("\#%02X%02X%02XFF" % [153, 102, 204],
                 Cairo::Color::AMETHYST.to_s)
  end

  # Android green: #A4C639: (164, 198, 57)
  test("Android green") do
    assert_equal("\#%02X%02X%02XFF" % [164, 198, 57],
                 Cairo::Color::ANDROID_GREEN.to_s)
  end

  # Anti-flash white: #F2F3F4: (242, 243, 244)
  test("Anti-flash white") do
    assert_equal("\#%02X%02X%02XFF" % [242, 243, 244],
                 Cairo::Color::ANTI_FLASH_WHITE.to_s)
  end

  # Antique brass: #CD9575: (205, 149, 117)
  test("Antique brass") do
    assert_equal("\#%02X%02X%02XFF" % [205, 149, 117],
                 Cairo::Color::ANTIQUE_BRASS.to_s)
  end

  # Antique bronze: #665D1E: (102, 93, 30)
  test("Antique bronze") do
    assert_equal("\#%02X%02X%02XFF" % [102, 93, 30],
                 Cairo::Color::ANTIQUE_BRONZE.to_s)
  end

  # Antique fuchsia: #915C83: (145, 92, 131)
  test("Antique fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [145, 92, 131],
                 Cairo::Color::ANTIQUE_FUCHSIA.to_s)
  end

  # Antique ruby: #841B2D: (132, 27, 45)
  test("Antique ruby") do
    assert_equal("\#%02X%02X%02XFF" % [132, 27, 45],
                 Cairo::Color::ANTIQUE_RUBY.to_s)
  end

  # Antique white: #FAEBD7: (250, 235, 215)
  test("Antique white") do
    assert_equal("\#%02X%02X%02XFF" % [250, 235, 215],
                 Cairo::Color::ANTIQUE_WHITE.to_s)
  end

  # Ao (English): #008000: (0, 128, 0)
  test("Ao (English)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 128, 0],
                 Cairo::Color::AO_ENGLISH.to_s)
  end

  # Apple: #66B447: (102, 180, 71)
  test("Apple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 180, 71],
                 Cairo::Color::APPLE.to_s)
  end

  # Apple green: #8DB600: (141, 182, 0)
  test("Apple green") do
    assert_equal("\#%02X%02X%02XFF" % [141, 182, 0],
                 Cairo::Color::APPLE_GREEN.to_s)
  end

  # Apricot: #FBCEB1: (251, 206, 177)
  test("Apricot") do
    assert_equal("\#%02X%02X%02XFF" % [251, 206, 177],
                 Cairo::Color::APRICOT.to_s)
  end

  # Aqua: #00FFFF: (0, 255, 255)
  test("Aqua") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                 Cairo::Color::AQUA.to_s)
  end

  # Aquamarine: #7FFFD4: (127, 255, 212)
  test("Aquamarine") do
    assert_equal("\#%02X%02X%02XFF" % [127, 255, 212],
                 Cairo::Color::AQUAMARINE.to_s)
  end

  # Arctic lime: #D0FF14: (208, 255, 20)
  test("Arctic lime") do
    assert_equal("\#%02X%02X%02XFF" % [208, 255, 20],
                 Cairo::Color::ARCTIC_LIME.to_s)
  end

  # Army green: #4B5320: (75, 83, 32)
  test("Army green") do
    assert_equal("\#%02X%02X%02XFF" % [75, 83, 32],
                 Cairo::Color::ARMY_GREEN.to_s)
  end

  # Artichoke: #8F9779: (143, 151, 121)
  test("Artichoke") do
    assert_equal("\#%02X%02X%02XFF" % [143, 151, 121],
                 Cairo::Color::ARTICHOKE.to_s)
  end

  # Arylide yellow: #E9D66B: (233, 214, 107)
  test("Arylide yellow") do
    assert_equal("\#%02X%02X%02XFF" % [233, 214, 107],
                 Cairo::Color::ARYLIDE_YELLOW.to_s)
  end

  # Ash grey: #B2BEB5: (178, 190, 181)
  test("Ash grey") do
    assert_equal("\#%02X%02X%02XFF" % [178, 190, 181],
                 Cairo::Color::ASH_GREY.to_s)
  end

  # Asparagus: #87A96B: (135, 169, 107)
  test("Asparagus") do
    assert_equal("\#%02X%02X%02XFF" % [135, 169, 107],
                 Cairo::Color::ASPARAGUS.to_s)
  end

  # Atomic tangerine: #FF9966: (255, 153, 102)
  test("Atomic tangerine") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 102],
                 Cairo::Color::ATOMIC_TANGERINE.to_s)
  end

  # Auburn: #A52A2A: (165, 42, 42)
  test("Auburn") do
    assert_equal("\#%02X%02X%02XFF" % [165, 42, 42],
                 Cairo::Color::AUBURN.to_s)
  end

  # Aureolin: #FDEE00: (253, 238, 0)
  test("Aureolin") do
    assert_equal("\#%02X%02X%02XFF" % [253, 238, 0],
                 Cairo::Color::AUREOLIN.to_s)
  end

  # AuroMetalSaurus: #6E7F80: (110, 127, 128)
  test("AuroMetalSaurus") do
    assert_equal("\#%02X%02X%02XFF" % [110, 127, 128],
                 Cairo::Color::AUROMETALSAURUS.to_s)
  end

  # Avocado: #568203: (86, 130, 3)
  test("Avocado") do
    assert_equal("\#%02X%02X%02XFF" % [86, 130, 3],
                 Cairo::Color::AVOCADO.to_s)
  end

  # Axolotl: #63775B: (99, 119, 91)
  test("Axolotl") do
    assert_equal("\#%02X%02X%02XFF" % [99, 119, 91],
                 Cairo::Color::AXOLOTL.to_s)
  end

  # Azure: #007FFF: (0, 127, 255)
  test("Azure") do
    assert_equal("\#%02X%02X%02XFF" % [0, 127, 255],
                 Cairo::Color::AZURE.to_s)
  end

  # Azure mist: #F0FFFF: (240, 255, 255)
  test("Azure mist") do
    assert_equal("\#%02X%02X%02XFF" % [240, 255, 255],
                 Cairo::Color::AZURE_MIST.to_s)
  end

  # B'dazzled blue: #2E5894: (46, 88, 149)
  test("B'dazzled blue") do
    assert_equal("\#%02X%02X%02XFF" % [46, 88, 149],
                 Cairo::Color::BDAZZLED_BLUE.to_s)
  end

  # Baby blue: #89CFF0: (137, 207, 240)
  test("Baby blue") do
    assert_equal("\#%02X%02X%02XFF" % [137, 207, 240],
                 Cairo::Color::BABY_BLUE.to_s)
  end

  # Baby blue eyes: #A1CAF1: (161, 202, 241)
  test("Baby blue eyes") do
    assert_equal("\#%02X%02X%02XFF" % [161, 202, 241],
                 Cairo::Color::BABY_BLUE_EYES.to_s)
  end

  # Baby pink: #F4C2C2: (244, 194, 194)
  test("Baby pink") do
    assert_equal("\#%02X%02X%02XFF" % [244, 194, 194],
                 Cairo::Color::BABY_PINK.to_s)
  end

  # Baby powder: #FEFEFA: (254, 254, 250)
  test("Baby powder") do
    assert_equal("\#%02X%02X%02XFF" % [254, 254, 250],
                 Cairo::Color::BABY_POWDER.to_s)
  end

  # Baker-Miller pink: #FF91AF: (255, 145, 175)
  test("Baker-Miller pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 145, 175],
                 Cairo::Color::BAKER_MILLER_PINK.to_s)
  end

  # Ball blue: #21ABCD: (33, 171, 205)
  test("Ball blue") do
    assert_equal("\#%02X%02X%02XFF" % [33, 171, 205],
                 Cairo::Color::BALL_BLUE.to_s)
  end

  # Banana Mania: #FAE7B5: (250, 231, 181)
  test("Banana Mania") do
    assert_equal("\#%02X%02X%02XFF" % [250, 231, 181],
                 Cairo::Color::BANANA_MANIA.to_s)
  end

  # Banana yellow: #FFE135: (255, 225, 53)
  test("Banana yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 225, 53],
                 Cairo::Color::BANANA_YELLOW.to_s)
  end

  # Bangladesh green: #006A4E: (0, 106, 78)
  test("Bangladesh green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 106, 78],
                 Cairo::Color::BANGLADESH_GREEN.to_s)
  end

  # Barbie pink: #E0218A: (224, 33, 138)
  test("Barbie pink") do
    assert_equal("\#%02X%02X%02XFF" % [224, 33, 138],
                 Cairo::Color::BARBIE_PINK.to_s)
  end

  # Barn red: #7C0A02: (124, 10, 2)
  test("Barn red") do
    assert_equal("\#%02X%02X%02XFF" % [124, 10, 2],
                 Cairo::Color::BARN_RED.to_s)
  end

  # Battery charged blue: #1DACD6: (29, 172, 214)
  test("Battery charged blue") do
    assert_equal("\#%02X%02X%02XFF" % [29, 172, 214],
                 Cairo::Color::BATTERY_CHARGED_BLUE.to_s)
  end

  # Battleship grey: #848482: (132, 132, 130)
  test("Battleship grey") do
    assert_equal("\#%02X%02X%02XFF" % [132, 132, 130],
                 Cairo::Color::BATTLESHIP_GREY.to_s)
  end

  # Bayside: #5FC9BF: (95, 201, 191)
  test("Bayside") do
    assert_equal("\#%02X%02X%02XFF" % [95, 201, 191],
                 Cairo::Color::BAYSIDE.to_s)
  end

  # Bazaar: #98777B: (152, 119, 123)
  test("Bazaar") do
    assert_equal("\#%02X%02X%02XFF" % [152, 119, 123],
                 Cairo::Color::BAZAAR.to_s)
  end

  # Beau blue: #BCD4E6: (188, 212, 230)
  test("Beau blue") do
    assert_equal("\#%02X%02X%02XFF" % [188, 212, 230],
                 Cairo::Color::BEAU_BLUE.to_s)
  end

  # Begonia: #FA6E79: (250, 110, 121)
  test("Begonia") do
    assert_equal("\#%02X%02X%02XFF" % [250, 110, 121],
                 Cairo::Color::BEGONIA.to_s)
  end

  # Beaver: #9F8170: (159, 129, 112)
  test("Beaver") do
    assert_equal("\#%02X%02X%02XFF" % [159, 129, 112],
                 Cairo::Color::BEAVER.to_s)
  end

  # Beer: #F28E1C: (242, 142, 28)
  test("Beer") do
    assert_equal("\#%02X%02X%02XFF" % [242, 142, 28],
                 Cairo::Color::BEER.to_s)
  end

  # Beige: #F5F5DC: (245, 245, 220)
  test("Beige") do
    assert_equal("\#%02X%02X%02XFF" % [245, 245, 220],
                 Cairo::Color::BEIGE.to_s)
  end

  # Big dip o’ruby: #9C2542: (156, 37, 66)
  test("Big dip o\u2019ruby") do
    assert_equal("\#%02X%02X%02XFF" % [156, 37, 66],
                 Cairo::Color::BIG_DIP_ORUBY.to_s)
  end

  # Big Foot Feet: #E88E5A: (232, 142, 90)
  test("Big Foot Feet") do
    assert_equal("\#%02X%02X%02XFF" % [232, 142, 90],
                 Cairo::Color::BIG_FOOT_FEET.to_s)
  end

  # Bisque: #FFE4C4: (255, 228, 196)
  test("Bisque") do
    assert_equal("\#%02X%02X%02XFF" % [255, 228, 196],
                 Cairo::Color::BISQUE.to_s)
  end

  # Bistre: #3D2B1F: (61, 43, 31)
  test("Bistre") do
    assert_equal("\#%02X%02X%02XFF" % [61, 43, 31],
                 Cairo::Color::BISTRE.to_s)
  end

  # Bistre brown: #967117: (150, 113, 23)
  test("Bistre brown") do
    assert_equal("\#%02X%02X%02XFF" % [150, 113, 23],
                 Cairo::Color::BISTRE_BROWN.to_s)
  end

  # Bitter lemon: #CAE00D: (202, 224, 13)
  test("Bitter lemon") do
    assert_equal("\#%02X%02X%02XFF" % [202, 224, 13],
                 Cairo::Color::BITTER_LEMON.to_s)
  end

  # Bitter lime: #BFFF00: (191, 255, 0)
  test("Bitter lime") do
    assert_equal("\#%02X%02X%02XFF" % [191, 255, 0],
                 Cairo::Color::BITTER_LIME.to_s)
  end

  # Bittersweet: #FE6F5E: (254, 111, 94)
  test("Bittersweet") do
    assert_equal("\#%02X%02X%02XFF" % [254, 111, 94],
                 Cairo::Color::BITTERSWEET.to_s)
  end

  # Bittersweet shimmer: #BF4F51: (191, 79, 81)
  test("Bittersweet shimmer") do
    assert_equal("\#%02X%02X%02XFF" % [191, 79, 81],
                 Cairo::Color::BITTERSWEET_SHIMMER.to_s)
  end

  # Black: #000000: (0, 0, 0)
  test("Black") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 0],
                 Cairo::Color::BLACK.to_s)
  end

  # Black bean: #3D0C02: (61, 12, 2)
  test("Black bean") do
    assert_equal("\#%02X%02X%02XFF" % [61, 12, 2],
                 Cairo::Color::BLACK_BEAN.to_s)
  end

  # Black chocolate: #1B1811: (27, 24, 17)
  test("Black chocolate") do
    assert_equal("\#%02X%02X%02XFF" % [27, 24, 17],
                 Cairo::Color::BLACK_CHOCOLATE.to_s)
  end

  # Black coffee: #3B2F2F: (59, 47, 47)
  test("Black coffee") do
    assert_equal("\#%02X%02X%02XFF" % [59, 47, 47],
                 Cairo::Color::BLACK_COFFEE.to_s)
  end

  # Black coral: #54626F: (84, 98, 111)
  test("Black coral") do
    assert_equal("\#%02X%02X%02XFF" % [84, 98, 111],
                 Cairo::Color::BLACK_CORAL.to_s)
  end

  # Black leather jacket: #253529: (37, 53, 41)
  test("Black leather jacket") do
    assert_equal("\#%02X%02X%02XFF" % [37, 53, 41],
                 Cairo::Color::BLACK_LEATHER_JACKET.to_s)
  end

  # Black olive: #3B3C36: (59, 60, 54)
  test("Black olive") do
    assert_equal("\#%02X%02X%02XFF" % [59, 60, 54],
                 Cairo::Color::BLACK_OLIVE.to_s)
  end

  # Blackberry: #8F5973: (143, 89, 115)
  test("Blackberry") do
    assert_equal("\#%02X%02X%02XFF" % [143, 89, 115],
                 Cairo::Color::BLACKBERRY.to_s)
  end

  # Black Shadows: #BFAFB2: (191, 175, 178)
  test("Black Shadows") do
    assert_equal("\#%02X%02X%02XFF" % [191, 175, 178],
                 Cairo::Color::BLACK_SHADOWS.to_s)
  end

  # Blanched almond: #FFEBCD: (255, 235, 205)
  test("Blanched almond") do
    assert_equal("\#%02X%02X%02XFF" % [255, 235, 205],
                 Cairo::Color::BLANCHED_ALMOND.to_s)
  end

  # Blast-off bronze: #A57164: (165, 113, 100)
  test("Blast-off bronze") do
    assert_equal("\#%02X%02X%02XFF" % [165, 113, 100],
                 Cairo::Color::BLAST_OFF_BRONZE.to_s)
  end

  # Bleu de France: #318CE7: (49, 140, 231)
  test("Bleu de France") do
    assert_equal("\#%02X%02X%02XFF" % [49, 140, 231],
                 Cairo::Color::BLEU_DE_FRANCE.to_s)
  end

  # Blizzard blue: #ACE5EE: (172, 229, 238)
  test("Blizzard blue") do
    assert_equal("\#%02X%02X%02XFF" % [172, 229, 238],
                 Cairo::Color::BLIZZARD_BLUE.to_s)
  end

  # Blond: #FAF0BE: (250, 240, 190)
  test("Blond") do
    assert_equal("\#%02X%02X%02XFF" % [250, 240, 190],
                 Cairo::Color::BLOND.to_s)
  end

  # Blood: #8A0303: (138, 3, 3)
  test("Blood") do
    assert_equal("\#%02X%02X%02XFF" % [138, 3, 3],
                 Cairo::Color::BLOOD.to_s)
  end

  # Blood orange: #D1001C: (210, 0, 27)
  test("Blood orange") do
    assert_equal("\#%02X%02X%02XFF" % [210, 0, 27],
                 Cairo::Color::BLOOD_ORANGE.to_s)
  end

  # Blood red: #660000: (102, 0, 0)
  test("Blood red") do
    assert_equal("\#%02X%02X%02XFF" % [102, 0, 0],
                 Cairo::Color::BLOOD_RED.to_s)
  end

  # Blood (Animal): #A41313: (164, 19, 19)
  test("Blood (Animal)") do
    assert_equal("\#%02X%02X%02XFF" % [164, 19, 19],
                 Cairo::Color::BLOOD_ANIMAL.to_s)
  end

  # Blood (organ): #630F0F: (99, 15, 15)
  test("Blood (organ)") do
    assert_equal("\#%02X%02X%02XFF" % [99, 15, 15],
                 Cairo::Color::BLOOD_ORGAN.to_s)
  end

  # Blue: #0000FF: (0, 0, 255)
  test("Blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 255],
                 Cairo::Color::BLUE.to_s)
  end

  # Blue (Crayola): #1F75FE: (31, 117, 254)
  test("Blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [31, 117, 254],
                 Cairo::Color::BLUE_CRAYOLA.to_s)
  end

  # Blue (Munsell): #0093AF: (0, 147, 175)
  test("Blue (Munsell)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 147, 175],
                 Cairo::Color::BLUE_MUNSELL.to_s)
  end

  # Blue (NCS): #0087BD: (0, 135, 189)
  test("Blue (NCS)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 135, 189],
                 Cairo::Color::BLUE_NCS.to_s)
  end

  # Blue (Pantone): #0018A8: (0, 24, 168)
  test("Blue (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 24, 168],
                 Cairo::Color::BLUE_PANTONE.to_s)
  end

  # Blue (pigment): #333399: (51, 51, 153)
  test("Blue (pigment)") do
    assert_equal("\#%02X%02X%02XFF" % [51, 51, 153],
                 Cairo::Color::BLUE_PIGMENT.to_s)
  end

  # Blue (RYB): #0247FE: (2, 71, 254)
  test("Blue (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [2, 71, 254],
                 Cairo::Color::BLUE_RYB.to_s)
  end

  # Blue bell: #A2A2D0: (162, 162, 208)
  test("Blue bell") do
    assert_equal("\#%02X%02X%02XFF" % [162, 162, 208],
                 Cairo::Color::BLUE_BELL.to_s)
  end

  # Blue bolt: #00B9FB: (0, 185, 251)
  test("Blue bolt") do
    assert_equal("\#%02X%02X%02XFF" % [0, 185, 251],
                 Cairo::Color::BLUE_BOLT.to_s)
  end

  # Blue cola: #0088DC: (0, 136, 220)
  test("Blue cola") do
    assert_equal("\#%02X%02X%02XFF" % [0, 136, 220],
                 Cairo::Color::BLUE_COLA.to_s)
  end

  # Blue-gray: #6699CC: (102, 153, 204)
  test("Blue-gray") do
    assert_equal("\#%02X%02X%02XFF" % [102, 153, 204],
                 Cairo::Color::BLUE_GRAY.to_s)
  end

  # Blue-green: #0D98BA: (13, 152, 186)
  test("Blue-green") do
    assert_equal("\#%02X%02X%02XFF" % [13, 152, 186],
                 Cairo::Color::BLUE_GREEN.to_s)
  end

  # Blue-green (color wheel): #064E40: (6, 78, 64)
  test("Blue-green (color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [6, 78, 64],
                 Cairo::Color::BLUE_GREEN_COLOR_WHEEL.to_s)
  end

  # Blue jeans: #5DADEC: (93, 173, 236)
  test("Blue jeans") do
    assert_equal("\#%02X%02X%02XFF" % [93, 173, 236],
                 Cairo::Color::BLUE_JEANS.to_s)
  end

  # Blue lagoon: #ACE5EE: (172, 229, 238)
  test("Blue lagoon") do
    assert_equal("\#%02X%02X%02XFF" % [172, 229, 238],
                 Cairo::Color::BLUE_LAGOON.to_s)
  end

  # Blue-magenta violet: #553592: (85, 53, 146)
  test("Blue-magenta violet") do
    assert_equal("\#%02X%02X%02XFF" % [85, 53, 146],
                 Cairo::Color::BLUE_MAGENTA_VIOLET.to_s)
  end

  # Blue raspberry: #0CBFE9: (12, 191, 233)
  test("Blue raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [12, 191, 233],
                 Cairo::Color::BLUE_RASPBERRY.to_s)
  end

  # Blue sapphire: #126180: (18, 97, 128)
  test("Blue sapphire") do
    assert_equal("\#%02X%02X%02XFF" % [18, 97, 128],
                 Cairo::Color::BLUE_SAPPHIRE.to_s)
  end

  # Blue-violet: #8A2BE2: (138, 43, 226)
  test("Blue-violet") do
    assert_equal("\#%02X%02X%02XFF" % [138, 43, 226],
                 Cairo::Color::BLUE_VIOLET.to_s)
  end

  # Blue-violet (Crayola): #7366BD: (115, 102, 189)
  test("Blue-violet (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [115, 102, 189],
                 Cairo::Color::BLUE_VIOLET_CRAYOLA.to_s)
  end

  # Blue-violet (color wheel): #4D1A7F: (77, 26, 127)
  test("Blue-violet (color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [77, 26, 127],
                 Cairo::Color::BLUE_VIOLET_COLOR_WHEEL.to_s)
  end

  # Blue yonder: #5072A7: (80, 114, 167)
  test("Blue yonder") do
    assert_equal("\#%02X%02X%02XFF" % [80, 114, 167],
                 Cairo::Color::BLUE_YONDER.to_s)
  end

  # Blueberry: #4F86F7: (79, 134, 247)
  test("Blueberry") do
    assert_equal("\#%02X%02X%02XFF" % [79, 134, 247],
                 Cairo::Color::BLUEBERRY.to_s)
  end

  # Bluebonnet: #1C1CF0: (28, 28, 240)
  test("Bluebonnet") do
    assert_equal("\#%02X%02X%02XFF" % [28, 28, 240],
                 Cairo::Color::BLUEBONNET.to_s)
  end

  # Blush: #DE5D83: (222, 93, 131)
  test("Blush") do
    assert_equal("\#%02X%02X%02XFF" % [222, 93, 131],
                 Cairo::Color::BLUSH.to_s)
  end

  # Bole: #79443B: (121, 68, 59)
  test("Bole") do
    assert_equal("\#%02X%02X%02XFF" % [121, 68, 59],
                 Cairo::Color::BOLE.to_s)
  end

  # Bondi blue: #0095B6: (0, 149, 182)
  test("Bondi blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 149, 182],
                 Cairo::Color::BONDI_BLUE.to_s)
  end

  # Bone: #E3DAC9: (227, 218, 201)
  test("Bone") do
    assert_equal("\#%02X%02X%02XFF" % [227, 218, 201],
                 Cairo::Color::BONE.to_s)
  end

  # Booger Buster: #DDE26A: (221, 226, 106)
  test("Booger Buster") do
    assert_equal("\#%02X%02X%02XFF" % [221, 226, 106],
                 Cairo::Color::BOOGER_BUSTER.to_s)
  end

  # Boston University red: #CC0000: (204, 0, 0)
  test("Boston University red") do
    assert_equal("\#%02X%02X%02XFF" % [204, 0, 0],
                 Cairo::Color::BOSTON_UNIVERSITY_RED.to_s)
  end

  # Bottle green: #006A4E: (0, 106, 78)
  test("Bottle green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 106, 78],
                 Cairo::Color::BOTTLE_GREEN.to_s)
  end

  # Boysenberry: #873260: (135, 50, 96)
  test("Boysenberry") do
    assert_equal("\#%02X%02X%02XFF" % [135, 50, 96],
                 Cairo::Color::BOYSENBERRY.to_s)
  end

  # Brandeis blue: #0070FF: (0, 112, 255)
  test("Brandeis blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 112, 255],
                 Cairo::Color::BRANDEIS_BLUE.to_s)
  end

  # Brandy: #87413F: (135, 65, 63)
  test("Brandy") do
    assert_equal("\#%02X%02X%02XFF" % [135, 65, 63],
                 Cairo::Color::BRANDY.to_s)
  end

  # Brave orange: #FF631C: (255, 99, 28)
  test("Brave orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 99, 28],
                 Cairo::Color::BRAVE_ORANGE.to_s)
  end

  # Brick red: #CB4154: (203, 65, 84)
  test("Brick red") do
    assert_equal("\#%02X%02X%02XFF" % [203, 65, 84],
                 Cairo::Color::BRICK_RED.to_s)
  end

  # Bright cerulean: #1DACD6: (29, 172, 214)
  test("Bright cerulean") do
    assert_equal("\#%02X%02X%02XFF" % [29, 172, 214],
                 Cairo::Color::BRIGHT_CERULEAN.to_s)
  end

  # Bright gray: #EBECF0: (235, 236, 240)
  test("Bright gray") do
    assert_equal("\#%02X%02X%02XFF" % [235, 236, 240],
                 Cairo::Color::BRIGHT_GRAY.to_s)
  end

  # Bright green: #66FF00: (102, 255, 0)
  test("Bright green") do
    assert_equal("\#%02X%02X%02XFF" % [102, 255, 0],
                 Cairo::Color::BRIGHT_GREEN.to_s)
  end

  # Briquette: #E0475C: (224, 71, 92)
  test("Briquette") do
    assert_equal("\#%02X%02X%02XFF" % [224, 71, 92],
                 Cairo::Color::BRIQUETTE.to_s)
  end

  # Bright lavender: #BF94E4: (191, 148, 228)
  test("Bright lavender") do
    assert_equal("\#%02X%02X%02XFF" % [191, 148, 228],
                 Cairo::Color::BRIGHT_LAVENDER.to_s)
  end

  # Bright lilac: #D891EF: (216, 145, 239)
  test("Bright lilac") do
    assert_equal("\#%02X%02X%02XFF" % [216, 145, 239],
                 Cairo::Color::BRIGHT_LILAC.to_s)
  end

  # Bright maroon: #C32148: (195, 33, 72)
  test("Bright maroon") do
    assert_equal("\#%02X%02X%02XFF" % [195, 33, 72],
                 Cairo::Color::BRIGHT_MAROON.to_s)
  end

  # Bright navy blue: #1974D2: (25, 116, 210)
  test("Bright navy blue") do
    assert_equal("\#%02X%02X%02XFF" % [25, 116, 210],
                 Cairo::Color::BRIGHT_NAVY_BLUE.to_s)
  end

  # Bright pink: #FF007F: (255, 0, 127)
  test("Bright pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 127],
                 Cairo::Color::BRIGHT_PINK.to_s)
  end

  # Bright turquoise: #08E8DE: (8, 232, 222)
  test("Bright turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [8, 232, 222],
                 Cairo::Color::BRIGHT_TURQUOISE.to_s)
  end

  # Bright ube: #D19FE8: (209, 159, 232)
  test("Bright ube") do
    assert_equal("\#%02X%02X%02XFF" % [209, 159, 232],
                 Cairo::Color::BRIGHT_UBE.to_s)
  end

  # Bright yellow (Crayola): #FFAA1D: (255, 170, 29)
  test("Bright yellow (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 170, 29],
                 Cairo::Color::BRIGHT_YELLOW_CRAYOLA.to_s)
  end

  # Brilliant azure: #3399FF: (51, 153, 255)
  test("Brilliant azure") do
    assert_equal("\#%02X%02X%02XFF" % [51, 153, 255],
                 Cairo::Color::BRILLIANT_AZURE.to_s)
  end

  # Brilliant lavender: #F4BBFF: (244, 187, 255)
  test("Brilliant lavender") do
    assert_equal("\#%02X%02X%02XFF" % [244, 187, 255],
                 Cairo::Color::BRILLIANT_LAVENDER.to_s)
  end

  # Brilliant rose: #FF55A3: (255, 85, 163)
  test("Brilliant rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 85, 163],
                 Cairo::Color::BRILLIANT_ROSE.to_s)
  end

  # Brink pink: #FB607F: (251, 96, 127)
  test("Brink pink") do
    assert_equal("\#%02X%02X%02XFF" % [251, 96, 127],
                 Cairo::Color::BRINK_PINK.to_s)
  end

  # British racing green: #004225: (0, 66, 37)
  test("British racing green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 66, 37],
                 Cairo::Color::BRITISH_RACING_GREEN.to_s)
  end

  # Bronze: #88540B: (136, 84, 11)
  test("Bronze") do
    assert_equal("\#%02X%02X%02XFF" % [136, 84, 11],
                 Cairo::Color::BRONZE.to_s)
  end

  # Bronze (metallic): #B08D57: (176, 140, 86)
  test("Bronze (metallic)") do
    assert_equal("\#%02X%02X%02XFF" % [176, 140, 86],
                 Cairo::Color::BRONZE_METALLIC.to_s)
  end

  # Bronze yellow: #737000: (115, 112, 0)
  test("Bronze yellow") do
    assert_equal("\#%02X%02X%02XFF" % [115, 112, 0],
                 Cairo::Color::BRONZE_YELLOW.to_s)
  end

  # Brown: #993300: (153, 51, 0)
  test("Brown") do
    assert_equal("\#%02X%02X%02XFF" % [153, 51, 0],
                 Cairo::Color::BROWN.to_s)
  end

  # Brown (Crayola): #AF593E: (175, 89, 62)
  test("Brown (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [175, 89, 62],
                 Cairo::Color::BROWN_CRAYOLA.to_s)
  end

  # Brown (traditional): #964B00: (150, 75, 0)
  test("Brown (traditional)") do
    assert_equal("\#%02X%02X%02XFF" % [150, 75, 0],
                 Cairo::Color::BROWN_TRADITIONAL.to_s)
  end

  # Brown (web): #A52A2A: (165, 42, 42)
  test("Brown (web)") do
    assert_equal("\#%02X%02X%02XFF" % [165, 42, 42],
                 Cairo::Color::BROWN_WEB.to_s)
  end

  # Brown-nose: #6B4423: (107, 68, 35)
  test("Brown-nose") do
    assert_equal("\#%02X%02X%02XFF" % [107, 68, 35],
                 Cairo::Color::BROWN_NOSE.to_s)
  end

  # Brown sugar: #AF6E4D: (175, 110, 77)
  test("Brown sugar") do
    assert_equal("\#%02X%02X%02XFF" % [175, 110, 77],
                 Cairo::Color::BROWN_SUGAR.to_s)
  end

  # Brunswick green: #1B4D3E: (27, 77, 62)
  test("Brunswick green") do
    assert_equal("\#%02X%02X%02XFF" % [27, 77, 62],
                 Cairo::Color::BRUNSWICK_GREEN.to_s)
  end

  # Bubble gum: #FFC1CC: (255, 193, 204)
  test("Bubble gum") do
    assert_equal("\#%02X%02X%02XFF" % [255, 193, 204],
                 Cairo::Color::BUBBLE_GUM.to_s)
  end

  # Bubbles: #E7FEFF: (231, 254, 255)
  test("Bubbles") do
    assert_equal("\#%02X%02X%02XFF" % [231, 254, 255],
                 Cairo::Color::BUBBLES.to_s)
  end

  # Bud green: #7BB661: (123, 182, 97)
  test("Bud green") do
    assert_equal("\#%02X%02X%02XFF" % [123, 182, 97],
                 Cairo::Color::BUD_GREEN.to_s)
  end

  # Buff: #F0DC82: (240, 220, 130)
  test("Buff") do
    assert_equal("\#%02X%02X%02XFF" % [240, 220, 130],
                 Cairo::Color::BUFF.to_s)
  end

  # Bulgarian rose: #480607: (72, 6, 7)
  test("Bulgarian rose") do
    assert_equal("\#%02X%02X%02XFF" % [72, 6, 7],
                 Cairo::Color::BULGARIAN_ROSE.to_s)
  end

  # Burgundy: #800020: (128, 0, 32)
  test("Burgundy") do
    assert_equal("\#%02X%02X%02XFF" % [128, 0, 32],
                 Cairo::Color::BURGUNDY.to_s)
  end

  # Burlywood: #DEB887: (222, 184, 135)
  test("Burlywood") do
    assert_equal("\#%02X%02X%02XFF" % [222, 184, 135],
                 Cairo::Color::BURLYWOOD.to_s)
  end

  # Burnished brown: #A17A74: (161, 122, 116)
  test("Burnished brown") do
    assert_equal("\#%02X%02X%02XFF" % [161, 122, 116],
                 Cairo::Color::BURNISHED_BROWN.to_s)
  end

  # Burnt orange: #CC5500: (204, 85, 0)
  test("Burnt orange") do
    assert_equal("\#%02X%02X%02XFF" % [204, 85, 0],
                 Cairo::Color::BURNT_ORANGE.to_s)
  end

  # Burnt sienna: #E97451: (233, 116, 81)
  test("Burnt sienna") do
    assert_equal("\#%02X%02X%02XFF" % [233, 116, 81],
                 Cairo::Color::BURNT_SIENNA.to_s)
  end

  # Burnt umber: #8A3324: (138, 51, 36)
  test("Burnt umber") do
    assert_equal("\#%02X%02X%02XFF" % [138, 51, 36],
                 Cairo::Color::BURNT_UMBER.to_s)
  end

  # Button blue: #24A0ED: (36, 160, 237)
  test("Button blue") do
    assert_equal("\#%02X%02X%02XFF" % [36, 160, 237],
                 Cairo::Color::BUTTON_BLUE.to_s)
  end

  # Byzantine: #BD33A4: (189, 51, 164)
  test("Byzantine") do
    assert_equal("\#%02X%02X%02XFF" % [189, 51, 164],
                 Cairo::Color::BYZANTINE.to_s)
  end

  # Byzantium: #702963: (112, 41, 99)
  test("Byzantium") do
    assert_equal("\#%02X%02X%02XFF" % [112, 41, 99],
                 Cairo::Color::BYZANTIUM.to_s)
  end

  # Cadet: #536872: (83, 104, 114)
  test("Cadet") do
    assert_equal("\#%02X%02X%02XFF" % [83, 104, 114],
                 Cairo::Color::CADET.to_s)
  end

  # Cadet blue: #5F9EA0: (95, 158, 160)
  test("Cadet blue") do
    assert_equal("\#%02X%02X%02XFF" % [95, 158, 160],
                 Cairo::Color::CADET_BLUE.to_s)
  end

  # Cadet blue (Crayola): #A9B2C3: (169, 178, 195)
  test("Cadet blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [169, 178, 195],
                 Cairo::Color::CADET_BLUE_CRAYOLA.to_s)
  end

  # Cadet grey: #91A3B0: (145, 163, 176)
  test("Cadet grey") do
    assert_equal("\#%02X%02X%02XFF" % [145, 163, 176],
                 Cairo::Color::CADET_GREY.to_s)
  end

  # Cadmium blue: #0A1195: (10, 17, 146)
  test("Cadmium blue") do
    assert_equal("\#%02X%02X%02XFF" % [10, 17, 146],
                 Cairo::Color::CADMIUM_BLUE.to_s)
  end

  # Cadmium green: #006B3C: (0, 107, 60)
  test("Cadmium green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 107, 60],
                 Cairo::Color::CADMIUM_GREEN.to_s)
  end

  # Cadmium orange: #ED872D: (237, 135, 45)
  test("Cadmium orange") do
    assert_equal("\#%02X%02X%02XFF" % [237, 135, 45],
                 Cairo::Color::CADMIUM_ORANGE.to_s)
  end

  # Cadmium purple: #B60C26: (182, 12, 38)
  test("Cadmium purple") do
    assert_equal("\#%02X%02X%02XFF" % [182, 12, 38],
                 Cairo::Color::CADMIUM_PURPLE.to_s)
  end

  # Cadmium red: #E30022: (227, 0, 34)
  test("Cadmium red") do
    assert_equal("\#%02X%02X%02XFF" % [227, 0, 34],
                 Cairo::Color::CADMIUM_RED.to_s)
  end

  # Cadmium yellow: #FFF600: (255, 246, 0)
  test("Cadmium yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 246, 0],
                 Cairo::Color::CADMIUM_YELLOW.to_s)
  end

  # Cadmium violet: #7F3E98: (127, 62, 152)
  test("Cadmium violet") do
    assert_equal("\#%02X%02X%02XFF" % [127, 62, 152],
                 Cairo::Color::CADMIUM_VIOLET.to_s)
  end

  # Café au lait: #A67B5B: (166, 123, 91)
  test("Caf\u00E9 au lait") do
    assert_equal("\#%02X%02X%02XFF" % [166, 123, 91],
                 Cairo::Color::CAFE_AU_LAIT.to_s)
  end

  # Café noir: #4B3621: (75, 54, 33)
  test("Caf\u00E9 noir") do
    assert_equal("\#%02X%02X%02XFF" % [75, 54, 33],
                 Cairo::Color::CAFE_NOIR.to_s)
  end

  # Cal Poly Pomona green: #1E4D2B: (30, 77, 43)
  test("Cal Poly Pomona green") do
    assert_equal("\#%02X%02X%02XFF" % [30, 77, 43],
                 Cairo::Color::CAL_POLY_POMONA_GREEN.to_s)
  end

  # Calamansi: #FCFFA4: (252, 255, 164)
  test("Calamansi") do
    assert_equal("\#%02X%02X%02XFF" % [252, 255, 164],
                 Cairo::Color::CALAMANSI.to_s)
  end

  # Cambridge blue: #A3C1AD: (163, 193, 173)
  test("Cambridge blue") do
    assert_equal("\#%02X%02X%02XFF" % [163, 193, 173],
                 Cairo::Color::CAMBRIDGE_BLUE.to_s)
  end

  # Camel: #C19A6B: (193, 154, 107)
  test("Camel") do
    assert_equal("\#%02X%02X%02XFF" % [193, 154, 107],
                 Cairo::Color::CAMEL.to_s)
  end

  # Cameo pink: #EFBBCC: (239, 187, 204)
  test("Cameo pink") do
    assert_equal("\#%02X%02X%02XFF" % [239, 187, 204],
                 Cairo::Color::CAMEO_PINK.to_s)
  end

  # Camouflage green: #78866B: (120, 134, 107)
  test("Camouflage green") do
    assert_equal("\#%02X%02X%02XFF" % [120, 134, 107],
                 Cairo::Color::CAMOUFLAGE_GREEN.to_s)
  end

  # Canary: #FFFF99: (255, 255, 153)
  test("Canary") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 153],
                 Cairo::Color::CANARY.to_s)
  end

  # Canary yellow: #FFEF00: (255, 239, 0)
  test("Canary yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 239, 0],
                 Cairo::Color::CANARY_YELLOW.to_s)
  end

  # Candy apple red: #FF0800: (255, 8, 0)
  test("Candy apple red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 8, 0],
                 Cairo::Color::CANDY_APPLE_RED.to_s)
  end

  # Candy pink: #E4717A: (228, 113, 122)
  test("Candy pink") do
    assert_equal("\#%02X%02X%02XFF" % [228, 113, 122],
                 Cairo::Color::CANDY_PINK.to_s)
  end

  # Capri: #00BFFF: (0, 191, 255)
  test("Capri") do
    assert_equal("\#%02X%02X%02XFF" % [0, 191, 255],
                 Cairo::Color::CAPRI.to_s)
  end

  # Caput mortuum: #592720: (89, 39, 32)
  test("Caput mortuum") do
    assert_equal("\#%02X%02X%02XFF" % [89, 39, 32],
                 Cairo::Color::CAPUT_MORTUUM.to_s)
  end

  # Caramel: #FFD59A: (255, 213, 154)
  test("Caramel") do
    assert_equal("\#%02X%02X%02XFF" % [255, 213, 154],
                 Cairo::Color::CARAMEL.to_s)
  end

  # Cardinal: #C41E3A: (196, 30, 58)
  test("Cardinal") do
    assert_equal("\#%02X%02X%02XFF" % [196, 30, 58],
                 Cairo::Color::CARDINAL.to_s)
  end

  # Caribbean green: #00CC99: (0, 204, 153)
  test("Caribbean green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 204, 153],
                 Cairo::Color::CARIBBEAN_GREEN.to_s)
  end

  # Carmine: #960018: (150, 0, 24)
  test("Carmine") do
    assert_equal("\#%02X%02X%02XFF" % [150, 0, 24],
                 Cairo::Color::CARMINE.to_s)
  end

  # Rich Carmine: #D70040: (215, 0, 64)
  test("Rich Carmine") do
    assert_equal("\#%02X%02X%02XFF" % [215, 0, 64],
                 Cairo::Color::RICH_CARMINE.to_s)
  end

  # Carmine pink: #EB4C42: (235, 76, 66)
  test("Carmine pink") do
    assert_equal("\#%02X%02X%02XFF" % [235, 76, 66],
                 Cairo::Color::CARMINE_PINK.to_s)
  end

  # Carmine red: #FF0038: (255, 0, 56)
  test("Carmine red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 56],
                 Cairo::Color::CARMINE_RED.to_s)
  end

  # Carnation pink: #FFA6C9: (255, 166, 201)
  test("Carnation pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 166, 201],
                 Cairo::Color::CARNATION_PINK.to_s)
  end

  # Carnelian: #B31B1B: (179, 27, 27)
  test("Carnelian") do
    assert_equal("\#%02X%02X%02XFF" % [179, 27, 27],
                 Cairo::Color::CARNELIAN.to_s)
  end

  # Carolina blue: #56A0D3: (86, 160, 211)
  test("Carolina blue") do
    assert_equal("\#%02X%02X%02XFF" % [86, 160, 211],
                 Cairo::Color::CAROLINA_BLUE.to_s)
  end

  # Carrot orange: #ED9121: (237, 145, 33)
  test("Carrot orange") do
    assert_equal("\#%02X%02X%02XFF" % [237, 145, 33],
                 Cairo::Color::CARROT_ORANGE.to_s)
  end

  # Castleton green: #00563F: (0, 86, 63)
  test("Castleton green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 86, 63],
                 Cairo::Color::CASTLETON_GREEN.to_s)
  end

  # Catalina blue: #062A78: (6, 42, 120)
  test("Catalina blue") do
    assert_equal("\#%02X%02X%02XFF" % [6, 42, 120],
                 Cairo::Color::CATALINA_BLUE.to_s)
  end

  # Catawba: #703642: (112, 54, 66)
  test("Catawba") do
    assert_equal("\#%02X%02X%02XFF" % [112, 54, 66],
                 Cairo::Color::CATAWBA.to_s)
  end

  # Cedar Chest: #C95A49: (201, 90, 73)
  test("Cedar Chest") do
    assert_equal("\#%02X%02X%02XFF" % [201, 90, 73],
                 Cairo::Color::CEDAR_CHEST.to_s)
  end

  # Ceil: #92A1CF: (146, 161, 207)
  test("Ceil") do
    assert_equal("\#%02X%02X%02XFF" % [146, 161, 207],
                 Cairo::Color::CEIL.to_s)
  end

  # Celadon: #ACE1AF: (172, 225, 175)
  test("Celadon") do
    assert_equal("\#%02X%02X%02XFF" % [172, 225, 175],
                 Cairo::Color::CELADON.to_s)
  end

  # Celadon blue: #007BA7: (0, 123, 167)
  test("Celadon blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 123, 167],
                 Cairo::Color::CELADON_BLUE.to_s)
  end

  # Celadon green: #2F847C: (47, 132, 124)
  test("Celadon green") do
    assert_equal("\#%02X%02X%02XFF" % [47, 132, 124],
                 Cairo::Color::CELADON_GREEN.to_s)
  end

  # Celeste: #B2FFFF: (178, 255, 255)
  test("Celeste") do
    assert_equal("\#%02X%02X%02XFF" % [178, 255, 255],
                 Cairo::Color::CELESTE.to_s)
  end

  # Celestial blue: #4997D0: (73, 151, 208)
  test("Celestial blue") do
    assert_equal("\#%02X%02X%02XFF" % [73, 151, 208],
                 Cairo::Color::CELESTIAL_BLUE.to_s)
  end

  # Celtic blue: #246BCE: (36, 107, 206)
  test("Celtic blue") do
    assert_equal("\#%02X%02X%02XFF" % [36, 107, 206],
                 Cairo::Color::CELTIC_BLUE.to_s)
  end

  # Cerise: #DE3163: (222, 49, 99)
  test("Cerise") do
    assert_equal("\#%02X%02X%02XFF" % [222, 49, 99],
                 Cairo::Color::CERISE.to_s)
  end

  # Cerise pink: #EC3B83: (236, 59, 131)
  test("Cerise pink") do
    assert_equal("\#%02X%02X%02XFF" % [236, 59, 131],
                 Cairo::Color::CERISE_PINK.to_s)
  end

  # Cerulean: #007BA7: (0, 123, 167)
  test("Cerulean") do
    assert_equal("\#%02X%02X%02XFF" % [0, 123, 167],
                 Cairo::Color::CERULEAN.to_s)
  end

  # Cerulean blue: #2A52BE: (42, 82, 190)
  test("Cerulean blue") do
    assert_equal("\#%02X%02X%02XFF" % [42, 82, 190],
                 Cairo::Color::CERULEAN_BLUE.to_s)
  end

  # Cetacean blue: #001440: (0, 20, 64)
  test("Cetacean blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 20, 64],
                 Cairo::Color::CETACEAN_BLUE.to_s)
  end

  # Cerulean frost: #6D9BC3: (109, 155, 195)
  test("Cerulean frost") do
    assert_equal("\#%02X%02X%02XFF" % [109, 155, 195],
                 Cairo::Color::CERULEAN_FROST.to_s)
  end

  # Cerulean (Crayola): #1DACD6: (29, 172, 214)
  test("Cerulean (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [29, 172, 214],
                 Cairo::Color::CERULEAN_CRAYOLA.to_s)
  end

  # CG blue: #007AA5: (0, 122, 165)
  test("CG blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 122, 165],
                 Cairo::Color::CG_BLUE.to_s)
  end

  # CG Red: #E03C31: (224, 60, 49)
  test("CG Red") do
    assert_equal("\#%02X%02X%02XFF" % [224, 60, 49],
                 Cairo::Color::CG_RED.to_s)
  end

  # Chambray: #ADBFC8: (173, 191, 200)
  test("Chambray") do
    assert_equal("\#%02X%02X%02XFF" % [173, 191, 200],
                 Cairo::Color::CHAMBRAY.to_s)
  end

  # Chamoisee: #A0785A: (160, 120, 90)
  test("Chamoisee") do
    assert_equal("\#%02X%02X%02XFF" % [160, 120, 90],
                 Cairo::Color::CHAMOISEE.to_s)
  end

  # Champagne: #F7E7CE: (247, 231, 206)
  test("Champagne") do
    assert_equal("\#%02X%02X%02XFF" % [247, 231, 206],
                 Cairo::Color::CHAMPAGNE.to_s)
  end

  # Champagne pink: #F1DDCF: (241, 221, 207)
  test("Champagne pink") do
    assert_equal("\#%02X%02X%02XFF" % [241, 221, 207],
                 Cairo::Color::CHAMPAGNE_PINK.to_s)
  end

  # Charcoal: #36454F: (54, 69, 79)
  test("Charcoal") do
    assert_equal("\#%02X%02X%02XFF" % [54, 69, 79],
                 Cairo::Color::CHARCOAL.to_s)
  end

  # Charleston green: #232B2B: (35, 43, 43)
  test("Charleston green") do
    assert_equal("\#%02X%02X%02XFF" % [35, 43, 43],
                 Cairo::Color::CHARLESTON_GREEN.to_s)
  end

  # Charm: #D0748B: (208, 116, 139)
  test("Charm") do
    assert_equal("\#%02X%02X%02XFF" % [208, 116, 139],
                 Cairo::Color::CHARM.to_s)
  end

  # Charm pink: #E68FAC: (230, 143, 172)
  test("Charm pink") do
    assert_equal("\#%02X%02X%02XFF" % [230, 143, 172],
                 Cairo::Color::CHARM_PINK.to_s)
  end

  # Chartreuse (traditional): #DFFF00: (223, 255, 0)
  test("Chartreuse (traditional)") do
    assert_equal("\#%02X%02X%02XFF" % [223, 255, 0],
                 Cairo::Color::CHARTREUSE_TRADITIONAL.to_s)
  end

  # Chartreuse (web): #7FFF00: (127, 255, 0)
  test("Chartreuse (web)") do
    assert_equal("\#%02X%02X%02XFF" % [127, 255, 0],
                 Cairo::Color::CHARTREUSE_WEB.to_s)
  end

  # Cheese: #FFA600: (255, 166, 0)
  test("Cheese") do
    assert_equal("\#%02X%02X%02XFF" % [255, 166, 0],
                 Cairo::Color::CHEESE.to_s)
  end

  # Cherry: #DE3163: (222, 49, 99)
  test("Cherry") do
    assert_equal("\#%02X%02X%02XFF" % [222, 49, 99],
                 Cairo::Color::CHERRY.to_s)
  end

  # Cherry blossom pink: #FFB7C5: (255, 183, 197)
  test("Cherry blossom pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 183, 197],
                 Cairo::Color::CHERRY_BLOSSOM_PINK.to_s)
  end

  # Chestnut: #954535: (149, 69, 53)
  test("Chestnut") do
    assert_equal("\#%02X%02X%02XFF" % [149, 69, 53],
                 Cairo::Color::CHESTNUT.to_s)
  end

  # China pink: #DE6FA1: (222, 111, 161)
  test("China pink") do
    assert_equal("\#%02X%02X%02XFF" % [222, 111, 161],
                 Cairo::Color::CHINA_PINK.to_s)
  end

  # China rose: #A8516E: (168, 81, 110)
  test("China rose") do
    assert_equal("\#%02X%02X%02XFF" % [168, 81, 110],
                 Cairo::Color::CHINA_ROSE.to_s)
  end

  # Chinese black: #141414: (20, 20, 20)
  test("Chinese black") do
    assert_equal("\#%02X%02X%02XFF" % [20, 20, 20],
                 Cairo::Color::CHINESE_BLACK.to_s)
  end

  # Chinese blue: #365194: (54, 81, 148)
  test("Chinese blue") do
    assert_equal("\#%02X%02X%02XFF" % [54, 81, 148],
                 Cairo::Color::CHINESE_BLUE.to_s)
  end

  # Chinese bronze: #CD8032: (205, 128, 50)
  test("Chinese bronze") do
    assert_equal("\#%02X%02X%02XFF" % [205, 128, 50],
                 Cairo::Color::CHINESE_BRONZE.to_s)
  end

  # Chinese brown: #AB381F: (170, 56, 30)
  test("Chinese brown") do
    assert_equal("\#%02X%02X%02XFF" % [170, 56, 30],
                 Cairo::Color::CHINESE_BROWN.to_s)
  end

  # Chinese green: #D0DB61: (208, 219, 97)
  test("Chinese green") do
    assert_equal("\#%02X%02X%02XFF" % [208, 219, 97],
                 Cairo::Color::CHINESE_GREEN.to_s)
  end

  # Chinese gold: #CC9900: (204, 153, 0)
  test("Chinese gold") do
    assert_equal("\#%02X%02X%02XFF" % [204, 153, 0],
                 Cairo::Color::CHINESE_GOLD.to_s)
  end

  # Chinese orange: #F37042: (243, 112, 66)
  test("Chinese orange") do
    assert_equal("\#%02X%02X%02XFF" % [243, 112, 66],
                 Cairo::Color::CHINESE_ORANGE.to_s)
  end

  # Chinese pink: #DE70A1: (222, 112, 161)
  test("Chinese pink") do
    assert_equal("\#%02X%02X%02XFF" % [222, 112, 161],
                 Cairo::Color::CHINESE_PINK.to_s)
  end

  # Chinese purple: #720B98: (114, 11, 152)
  test("Chinese purple") do
    assert_equal("\#%02X%02X%02XFF" % [114, 11, 152],
                 Cairo::Color::CHINESE_PURPLE.to_s)
  end

  # Chinese red: #CD071E: (205, 7, 30)
  test("Chinese red") do
    assert_equal("\#%02X%02X%02XFF" % [205, 7, 30],
                 Cairo::Color::CHINESE_RED.to_s)
  end

  # Chinese silver: #CCCCCC: (204, 204, 204)
  test("Chinese silver") do
    assert_equal("\#%02X%02X%02XFF" % [204, 204, 204],
                 Cairo::Color::CHINESE_SILVER.to_s)
  end

  # Chinese violet: #856088: (133, 96, 136)
  test("Chinese violet") do
    assert_equal("\#%02X%02X%02XFF" % [133, 96, 136],
                 Cairo::Color::CHINESE_VIOLET.to_s)
  end

  # Chinese white: #E2E5DE: (226, 229, 222)
  test("Chinese white") do
    assert_equal("\#%02X%02X%02XFF" % [226, 229, 222],
                 Cairo::Color::CHINESE_WHITE.to_s)
  end

  # Chinese yellow: #FFB200: (255, 178, 0)
  test("Chinese yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 178, 0],
                 Cairo::Color::CHINESE_YELLOW.to_s)
  end

  # Chlorophyll green: #4AFF00: (74, 255, 0)
  test("Chlorophyll green") do
    assert_equal("\#%02X%02X%02XFF" % [74, 255, 0],
                 Cairo::Color::CHLOROPHYLL_GREEN.to_s)
  end

  # Chocolate brown: #3F000F: (63, 0, 15)
  test("Chocolate brown") do
    assert_equal("\#%02X%02X%02XFF" % [63, 0, 15],
                 Cairo::Color::CHOCOLATE_BROWN.to_s)
  end

  # Chocolate cosmos: #58111A: (88, 17, 26)
  test("Chocolate cosmos") do
    assert_equal("\#%02X%02X%02XFF" % [88, 17, 26],
                 Cairo::Color::CHOCOLATE_COSMOS.to_s)
  end

  # Chocolate Kisses: #3C1421: (60, 20, 33)
  test("Chocolate Kisses") do
    assert_equal("\#%02X%02X%02XFF" % [60, 20, 33],
                 Cairo::Color::CHOCOLATE_KISSES.to_s)
  end

  # Chocolate (traditional): #7B3F00: (123, 63, 0)
  test("Chocolate (traditional)") do
    assert_equal("\#%02X%02X%02XFF" % [123, 63, 0],
                 Cairo::Color::CHOCOLATE_TRADITIONAL.to_s)
  end

  # Chocolate (web): #D2691E: (210, 105, 30)
  test("Chocolate (web)") do
    assert_equal("\#%02X%02X%02XFF" % [210, 105, 30],
                 Cairo::Color::CHOCOLATE_WEB.to_s)
  end

  # Christmas blue: #2A8FBD: (42, 143, 189)
  test("Christmas blue") do
    assert_equal("\#%02X%02X%02XFF" % [42, 143, 189],
                 Cairo::Color::CHRISTMAS_BLUE.to_s)
  end

  # Christmas brown: #5D2B2C: (93, 43, 44)
  test("Christmas brown") do
    assert_equal("\#%02X%02X%02XFF" % [93, 43, 44],
                 Cairo::Color::CHRISTMAS_BROWN.to_s)
  end

  # Christmas green: #3C8D0D: (60, 141, 13)
  test("Christmas green") do
    assert_equal("\#%02X%02X%02XFF" % [60, 141, 13],
                 Cairo::Color::CHRISTMAS_GREEN.to_s)
  end

  # Christmas gold: #CAA906: (202, 169, 6)
  test("Christmas gold") do
    assert_equal("\#%02X%02X%02XFF" % [202, 169, 6],
                 Cairo::Color::CHRISTMAS_GOLD.to_s)
  end

  # Christmas orange: #FF6600: (255, 102, 0)
  test("Christmas orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 102, 0],
                 Cairo::Color::CHRISTMAS_ORANGE.to_s)
  end

  # Christmas pink: #FFCCCB: (255, 204, 203)
  test("Christmas pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 204, 203],
                 Cairo::Color::CHRISTMAS_PINK.to_s)
  end

  # Christmas purple: #663398: (102, 51, 152)
  test("Christmas purple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 51, 152],
                 Cairo::Color::CHRISTMAS_PURPLE.to_s)
  end

  # Christmas red: #AA0114: (170, 1, 20)
  test("Christmas red") do
    assert_equal("\#%02X%02X%02XFF" % [170, 1, 20],
                 Cairo::Color::CHRISTMAS_RED.to_s)
  end

  # Christmas silver: #E1DFE0: (225, 223, 224)
  test("Christmas silver") do
    assert_equal("\#%02X%02X%02XFF" % [225, 223, 224],
                 Cairo::Color::CHRISTMAS_SILVER.to_s)
  end

  # Christmas yellow: #FFCC00: (255, 204, 0)
  test("Christmas yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 204, 0],
                 Cairo::Color::CHRISTMAS_YELLOW.to_s)
  end

  # Chrome yellow: #FFA700: (255, 167, 0)
  test("Chrome yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 167, 0],
                 Cairo::Color::CHROME_YELLOW.to_s)
  end

  # Cinereous: #98817B: (152, 129, 123)
  test("Cinereous") do
    assert_equal("\#%02X%02X%02XFF" % [152, 129, 123],
                 Cairo::Color::CINEREOUS.to_s)
  end

  # Cinnabar: #E34234: (227, 66, 52)
  test("Cinnabar") do
    assert_equal("\#%02X%02X%02XFF" % [227, 66, 52],
                 Cairo::Color::CINNABAR.to_s)
  end

  # Cinnamon: #D2691E: (210, 105, 30)
  test("Cinnamon") do
    assert_equal("\#%02X%02X%02XFF" % [210, 105, 30],
                 Cairo::Color::CINNAMON.to_s)
  end

  # Cinnamon Satin: #CD607E: (205, 96, 126)
  test("Cinnamon Satin") do
    assert_equal("\#%02X%02X%02XFF" % [205, 96, 126],
                 Cairo::Color::CINNAMON_SATIN.to_s)
  end

  # Citrine: #E4D00A: (228, 208, 10)
  test("Citrine") do
    assert_equal("\#%02X%02X%02XFF" % [228, 208, 10],
                 Cairo::Color::CITRINE.to_s)
  end

  # Citrine Brown: #933709: (147, 55, 9)
  test("Citrine Brown") do
    assert_equal("\#%02X%02X%02XFF" % [147, 55, 9],
                 Cairo::Color::CITRINE_BROWN.to_s)
  end

  # Citron: #9FA91F: (158, 169, 31)
  test("Citron") do
    assert_equal("\#%02X%02X%02XFF" % [158, 169, 31],
                 Cairo::Color::CITRON.to_s)
  end

  # Claret: #7F1734: (127, 23, 52)
  test("Claret") do
    assert_equal("\#%02X%02X%02XFF" % [127, 23, 52],
                 Cairo::Color::CLARET.to_s)
  end

  # Classic rose: #FBCCE7: (251, 204, 231)
  test("Classic rose") do
    assert_equal("\#%02X%02X%02XFF" % [251, 204, 231],
                 Cairo::Color::CLASSIC_ROSE.to_s)
  end

  # Cobalt blue: #0047AB: (0, 71, 171)
  test("Cobalt blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 71, 171],
                 Cairo::Color::COBALT_BLUE.to_s)
  end

  # Cocoa brown: #D2691E: (210, 105, 30)
  test("Cocoa brown") do
    assert_equal("\#%02X%02X%02XFF" % [210, 105, 30],
                 Cairo::Color::COCOA_BROWN.to_s)
  end

  # Coconut: #965A3E: (150, 90, 62)
  test("Coconut") do
    assert_equal("\#%02X%02X%02XFF" % [150, 90, 62],
                 Cairo::Color::COCONUT.to_s)
  end

  # Coffee: #6F4E37: (111, 78, 55)
  test("Coffee") do
    assert_equal("\#%02X%02X%02XFF" % [111, 78, 55],
                 Cairo::Color::COFFEE.to_s)
  end

  # Cola: #3C3024: (60, 48, 36)
  test("Cola") do
    assert_equal("\#%02X%02X%02XFF" % [60, 48, 36],
                 Cairo::Color::COLA.to_s)
  end

  # Columbia Blue: #C4D8E2: (196, 216, 226)
  test("Columbia Blue") do
    assert_equal("\#%02X%02X%02XFF" % [196, 216, 226],
                 Cairo::Color::COLUMBIA_BLUE.to_s)
  end

  # Conditioner: #FFFFCC: (255, 255, 204)
  test("Conditioner") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 204],
                 Cairo::Color::CONDITIONER.to_s)
  end

  # Congo pink: #F88379: (248, 131, 121)
  test("Congo pink") do
    assert_equal("\#%02X%02X%02XFF" % [248, 131, 121],
                 Cairo::Color::CONGO_PINK.to_s)
  end

  # Cool black: #002E63: (0, 46, 99)
  test("Cool black") do
    assert_equal("\#%02X%02X%02XFF" % [0, 46, 99],
                 Cairo::Color::COOL_BLACK.to_s)
  end

  # Cool grey: #8C92AC: (140, 146, 172)
  test("Cool grey") do
    assert_equal("\#%02X%02X%02XFF" % [140, 146, 172],
                 Cairo::Color::COOL_GREY.to_s)
  end

  # Cookies and cream: #EEE0B1: (238, 224, 177)
  test("Cookies and cream") do
    assert_equal("\#%02X%02X%02XFF" % [238, 224, 177],
                 Cairo::Color::COOKIES_AND_CREAM.to_s)
  end

  # Copper: #B87333: (184, 115, 51)
  test("Copper") do
    assert_equal("\#%02X%02X%02XFF" % [184, 115, 51],
                 Cairo::Color::COPPER.to_s)
  end

  # Copper (Crayola): #DA8A67: (218, 138, 103)
  test("Copper (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [218, 138, 103],
                 Cairo::Color::COPPER_CRAYOLA.to_s)
  end

  # Copper penny: #AD6F69: (173, 111, 105)
  test("Copper penny") do
    assert_equal("\#%02X%02X%02XFF" % [173, 111, 105],
                 Cairo::Color::COPPER_PENNY.to_s)
  end

  # Copper red: #CB6D51: (203, 109, 81)
  test("Copper red") do
    assert_equal("\#%02X%02X%02XFF" % [203, 109, 81],
                 Cairo::Color::COPPER_RED.to_s)
  end

  # Copper rose: #996666: (153, 102, 102)
  test("Copper rose") do
    assert_equal("\#%02X%02X%02XFF" % [153, 102, 102],
                 Cairo::Color::COPPER_ROSE.to_s)
  end

  # Coquelicot: #FF3800: (255, 56, 0)
  test("Coquelicot") do
    assert_equal("\#%02X%02X%02XFF" % [255, 56, 0],
                 Cairo::Color::COQUELICOT.to_s)
  end

  # Coral: #FF7F50: (255, 127, 80)
  test("Coral") do
    assert_equal("\#%02X%02X%02XFF" % [255, 127, 80],
                 Cairo::Color::CORAL.to_s)
  end

  # Coral pink: #F88379: (248, 131, 121)
  test("Coral pink") do
    assert_equal("\#%02X%02X%02XFF" % [248, 131, 121],
                 Cairo::Color::CORAL_PINK.to_s)
  end

  # Coral red: #FF4040: (255, 64, 64)
  test("Coral red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 64, 64],
                 Cairo::Color::CORAL_RED.to_s)
  end

  # Coral reef: #FD7C6E: (253, 124, 110)
  test("Coral reef") do
    assert_equal("\#%02X%02X%02XFF" % [253, 124, 110],
                 Cairo::Color::CORAL_REEF.to_s)
  end

  # Coral Reef (Valspar Paint Color): #F6A494: (246, 164, 148)
  test("Coral Reef (Valspar Paint Color)") do
    assert_equal("\#%02X%02X%02XFF" % [246, 164, 148],
                 Cairo::Color::CORAL_REEF_VALSPAR_PAINT_COLOR.to_s)
  end

  # Cordovan: #893F45: (137, 63, 69)
  test("Cordovan") do
    assert_equal("\#%02X%02X%02XFF" % [137, 63, 69],
                 Cairo::Color::CORDOVAN.to_s)
  end

  # Corn: #FBEC5D: (251, 236, 93)
  test("Corn") do
    assert_equal("\#%02X%02X%02XFF" % [251, 236, 93],
                 Cairo::Color::CORN.to_s)
  end

  # Cornell red: #B31B1B: (179, 27, 27)
  test("Cornell red") do
    assert_equal("\#%02X%02X%02XFF" % [179, 27, 27],
                 Cairo::Color::CORNELL_RED.to_s)
  end

  # Cornflower blue: #6495ED: (100, 149, 237)
  test("Cornflower blue") do
    assert_equal("\#%02X%02X%02XFF" % [100, 149, 237],
                 Cairo::Color::CORNFLOWER_BLUE.to_s)
  end

  # Cornflower: #93CCEA: (1, 159, 222)
  test("Cornflower") do
    assert_equal("\#%02X%02X%02XFF" % [1, 159, 222],
                 Cairo::Color::CORNFLOWER.to_s)
  end

  # Cornsilk: #FFF8DC: (255, 248, 220)
  test("Cornsilk") do
    assert_equal("\#%02X%02X%02XFF" % [255, 248, 220],
                 Cairo::Color::CORNSILK.to_s)
  end

  # Cosmic cobalt: #2E2D88: (46, 45, 136)
  test("Cosmic cobalt") do
    assert_equal("\#%02X%02X%02XFF" % [46, 45, 136],
                 Cairo::Color::COSMIC_COBALT.to_s)
  end

  # Cosmic latte: #FFF8E7: (255, 248, 231)
  test("Cosmic latte") do
    assert_equal("\#%02X%02X%02XFF" % [255, 248, 231],
                 Cairo::Color::COSMIC_LATTE.to_s)
  end

  # Coyote brown: #81613C: (129, 97, 60)
  test("Coyote brown") do
    assert_equal("\#%02X%02X%02XFF" % [129, 97, 60],
                 Cairo::Color::COYOTE_BROWN.to_s)
  end

  # Cotton candy: #FFBCD9: (255, 188, 217)
  test("Cotton candy") do
    assert_equal("\#%02X%02X%02XFF" % [255, 188, 217],
                 Cairo::Color::COTTON_CANDY.to_s)
  end

  # Cream: #FFFDD0: (255, 253, 208)
  test("Cream") do
    assert_equal("\#%02X%02X%02XFF" % [255, 253, 208],
                 Cairo::Color::CREAM.to_s)
  end

  # Crimson: #DC143C: (220, 20, 60)
  test("Crimson") do
    assert_equal("\#%02X%02X%02XFF" % [220, 20, 60],
                 Cairo::Color::CRIMSON.to_s)
  end

  # Crimson glory: #BE0032: (190, 0, 50)
  test("Crimson glory") do
    assert_equal("\#%02X%02X%02XFF" % [190, 0, 50],
                 Cairo::Color::CRIMSON_GLORY.to_s)
  end

  # Crimson red: #990000: (153, 0, 0)
  test("Crimson red") do
    assert_equal("\#%02X%02X%02XFF" % [153, 0, 0],
                 Cairo::Color::CRIMSON_RED.to_s)
  end

  # Cultured: #F5F5F5: (245, 245, 245)
  test("Cultured") do
    assert_equal("\#%02X%02X%02XFF" % [245, 245, 245],
                 Cairo::Color::CULTURED.to_s)
  end

  # Cyan: #00FFFF: (0, 255, 255)
  test("Cyan") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                 Cairo::Color::CYAN.to_s)
  end

  # Cyan azure: #4E82B4: (78, 130, 180)
  test("Cyan azure") do
    assert_equal("\#%02X%02X%02XFF" % [78, 130, 180],
                 Cairo::Color::CYAN_AZURE.to_s)
  end

  # Cyan-blue azure: #4682BF: (70, 130, 191)
  test("Cyan-blue azure") do
    assert_equal("\#%02X%02X%02XFF" % [70, 130, 191],
                 Cairo::Color::CYAN_BLUE_AZURE.to_s)
  end

  # Cyan cobalt blue: #28589C: (40, 88, 156)
  test("Cyan cobalt blue") do
    assert_equal("\#%02X%02X%02XFF" % [40, 88, 156],
                 Cairo::Color::CYAN_COBALT_BLUE.to_s)
  end

  # Cyan cornflower blue: #188BC2: (24, 139, 194)
  test("Cyan cornflower blue") do
    assert_equal("\#%02X%02X%02XFF" % [24, 139, 194],
                 Cairo::Color::CYAN_CORNFLOWER_BLUE.to_s)
  end

  # Cyan (process): #00B7EB: (0, 183, 235)
  test("Cyan (process)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 183, 235],
                 Cairo::Color::CYAN_PROCESS.to_s)
  end

  # Cyber grape: #58427C: (88, 66, 124)
  test("Cyber grape") do
    assert_equal("\#%02X%02X%02XFF" % [88, 66, 124],
                 Cairo::Color::CYBER_GRAPE.to_s)
  end

  # Cyber yellow: #FFD300: (255, 211, 0)
  test("Cyber yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 211, 0],
                 Cairo::Color::CYBER_YELLOW.to_s)
  end

  # Cyclamen: #F56FA1: (245, 111, 161)
  test("Cyclamen") do
    assert_equal("\#%02X%02X%02XFF" % [245, 111, 161],
                 Cairo::Color::CYCLAMEN.to_s)
  end

  # Daffodil: #FFFF31: (255, 255, 49)
  test("Daffodil") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 49],
                 Cairo::Color::DAFFODIL.to_s)
  end

  # Dandelion: #F0E130: (240, 225, 48)
  test("Dandelion") do
    assert_equal("\#%02X%02X%02XFF" % [240, 225, 48],
                 Cairo::Color::DANDELION.to_s)
  end

  # Dandelion (Crayola): #FDDB6D: (253, 219, 109)
  test("Dandelion (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [253, 219, 109],
                 Cairo::Color::DANDELION_CRAYOLA.to_s)
  end

  # Dark blue: #00008B: (0, 0, 139)
  test("Dark blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 139],
                 Cairo::Color::DARK_BLUE.to_s)
  end

  # Dark blue-gray: #666699: (102, 102, 153)
  test("Dark blue-gray") do
    assert_equal("\#%02X%02X%02XFF" % [102, 102, 153],
                 Cairo::Color::DARK_BLUE_GRAY.to_s)
  end

  # Dark bronze: #804A00: (128, 74, 45)
  test("Dark bronze") do
    assert_equal("\#%02X%02X%02XFF" % [128, 74, 45],
                 Cairo::Color::DARK_BRONZE.to_s)
  end

  # Dark bronze (Coin): #514100: (81, 65, 0)
  test("Dark bronze (Coin)") do
    assert_equal("\#%02X%02X%02XFF" % [81, 65, 0],
                 Cairo::Color::DARK_BRONZE_COIN.to_s)
  end

  # Dark brown: #654321: (101, 67, 33)
  test("Dark brown") do
    assert_equal("\#%02X%02X%02XFF" % [101, 67, 33],
                 Cairo::Color::DARK_BROWN.to_s)
  end

  # Dark brown-tangelo: #88654E: (136, 101, 78)
  test("Dark brown-tangelo") do
    assert_equal("\#%02X%02X%02XFF" % [136, 101, 78],
                 Cairo::Color::DARK_BROWN_TANGELO.to_s)
  end

  # Dark byzantium: #5D3954: (93, 57, 84)
  test("Dark byzantium") do
    assert_equal("\#%02X%02X%02XFF" % [93, 57, 84],
                 Cairo::Color::DARK_BYZANTIUM.to_s)
  end

  # Dark candy apple red: #A40000: (164, 0, 0)
  test("Dark candy apple red") do
    assert_equal("\#%02X%02X%02XFF" % [164, 0, 0],
                 Cairo::Color::DARK_CANDY_APPLE_RED.to_s)
  end

  # Dark cerulean: #08457E: (8, 69, 126)
  test("Dark cerulean") do
    assert_equal("\#%02X%02X%02XFF" % [8, 69, 126],
                 Cairo::Color::DARK_CERULEAN.to_s)
  end

  # Dark charcoal: #333333: (51, 51, 51)
  test("Dark charcoal") do
    assert_equal("\#%02X%02X%02XFF" % [51, 51, 51],
                 Cairo::Color::DARK_CHARCOAL.to_s)
  end

  # Dark chestnut: #986960: (152, 105, 96)
  test("Dark chestnut") do
    assert_equal("\#%02X%02X%02XFF" % [152, 105, 96],
                 Cairo::Color::DARK_CHESTNUT.to_s)
  end

  # Dark chocolate: #490206: (73, 2, 6)
  test("Dark chocolate") do
    assert_equal("\#%02X%02X%02XFF" % [73, 2, 6],
                 Cairo::Color::DARK_CHOCOLATE.to_s)
  end

  # Dark chocolate (Hershey's): #3C1321: (60, 19, 33)
  test("Dark chocolate (Hershey's)") do
    assert_equal("\#%02X%02X%02XFF" % [60, 19, 33],
                 Cairo::Color::DARK_CHOCOLATE_HERSHEYS.to_s)
  end

  # Dark cornflower blue: #26428B: (38, 66, 139)
  test("Dark cornflower blue") do
    assert_equal("\#%02X%02X%02XFF" % [38, 66, 139],
                 Cairo::Color::DARK_CORNFLOWER_BLUE.to_s)
  end

  # Dark coral: #CD5B45: (205, 91, 69)
  test("Dark coral") do
    assert_equal("\#%02X%02X%02XFF" % [205, 91, 69],
                 Cairo::Color::DARK_CORAL.to_s)
  end

  # Dark cyan: #008B8B: (0, 139, 139)
  test("Dark cyan") do
    assert_equal("\#%02X%02X%02XFF" % [0, 139, 139],
                 Cairo::Color::DARK_CYAN.to_s)
  end

  # Dark electric blue: #536878: (83, 104, 120)
  test("Dark electric blue") do
    assert_equal("\#%02X%02X%02XFF" % [83, 104, 120],
                 Cairo::Color::DARK_ELECTRIC_BLUE.to_s)
  end

  # Dark gold: #AA6C39: (170, 108, 57)
  test("Dark gold") do
    assert_equal("\#%02X%02X%02XFF" % [170, 108, 57],
                 Cairo::Color::DARK_GOLD.to_s)
  end

  # Dark goldenrod: #B8860B: (184, 134, 11)
  test("Dark goldenrod") do
    assert_equal("\#%02X%02X%02XFF" % [184, 134, 11],
                 Cairo::Color::DARK_GOLDENROD.to_s)
  end

  # Dark gray (X11): #A9A9A9: (169, 169, 169)
  test("Dark gray (X11)") do
    assert_equal("\#%02X%02X%02XFF" % [169, 169, 169],
                 Cairo::Color::DARK_GRAY_X11.to_s)
  end

  # Dark green: #013220: (1, 50, 32)
  test("Dark green") do
    assert_equal("\#%02X%02X%02XFF" % [1, 50, 32],
                 Cairo::Color::DARK_GREEN.to_s)
  end

  # Dark green (X11): #006400: (0, 100, 0)
  test("Dark green (X11)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 100, 0],
                 Cairo::Color::DARK_GREEN_X11.to_s)
  end

  # Dark gunmetal: #1F262A: (31, 38, 42)
  test("Dark gunmetal") do
    assert_equal("\#%02X%02X%02XFF" % [31, 38, 42],
                 Cairo::Color::DARK_GUNMETAL.to_s)
  end

  # Dark imperial blue: #00416A: (0, 65, 106)
  test("Dark imperial blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 65, 106],
                 Cairo::Color::DARK_IMPERIAL_BLUE.to_s)
  end

  # Dark jungle green: #1A2421: (26, 36, 33)
  test("Dark jungle green") do
    assert_equal("\#%02X%02X%02XFF" % [26, 36, 33],
                 Cairo::Color::DARK_JUNGLE_GREEN.to_s)
  end

  # Dark khaki: #BDB76B: (189, 183, 107)
  test("Dark khaki") do
    assert_equal("\#%02X%02X%02XFF" % [189, 183, 107],
                 Cairo::Color::DARK_KHAKI.to_s)
  end

  # Dark lava: #483C32: (72, 60, 50)
  test("Dark lava") do
    assert_equal("\#%02X%02X%02XFF" % [72, 60, 50],
                 Cairo::Color::DARK_LAVA.to_s)
  end

  # Dark lavender: #734F96: (115, 79, 150)
  test("Dark lavender") do
    assert_equal("\#%02X%02X%02XFF" % [115, 79, 150],
                 Cairo::Color::DARK_LAVENDER.to_s)
  end

  # Dark lemon lime: #8BBE1B: (139, 190, 27)
  test("Dark lemon lime") do
    assert_equal("\#%02X%02X%02XFF" % [139, 190, 27],
                 Cairo::Color::DARK_LEMON_LIME.to_s)
  end

  # Dark liver: #534B4F: (83, 75, 79)
  test("Dark liver") do
    assert_equal("\#%02X%02X%02XFF" % [83, 75, 79],
                 Cairo::Color::DARK_LIVER.to_s)
  end

  # Dark liver (horses): #543D37: (84, 61, 55)
  test("Dark liver (horses)") do
    assert_equal("\#%02X%02X%02XFF" % [84, 61, 55],
                 Cairo::Color::DARK_LIVER_HORSES.to_s)
  end

  # Dark magenta: #8B008B: (139, 0, 139)
  test("Dark magenta") do
    assert_equal("\#%02X%02X%02XFF" % [139, 0, 139],
                 Cairo::Color::DARK_MAGENTA.to_s)
  end

  # Dark medium gray: #A9A9A9: (169, 169, 169)
  test("Dark medium gray") do
    assert_equal("\#%02X%02X%02XFF" % [169, 169, 169],
                 Cairo::Color::DARK_MEDIUM_GRAY.to_s)
  end

  # Dark midnight blue: #003366: (0, 51, 102)
  test("Dark midnight blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 51, 102],
                 Cairo::Color::DARK_MIDNIGHT_BLUE.to_s)
  end

  # Dark moss green: #4A5D23: (74, 93, 35)
  test("Dark moss green") do
    assert_equal("\#%02X%02X%02XFF" % [74, 93, 35],
                 Cairo::Color::DARK_MOSS_GREEN.to_s)
  end

  # Dark olive green: #556B2F: (85, 107, 47)
  test("Dark olive green") do
    assert_equal("\#%02X%02X%02XFF" % [85, 107, 47],
                 Cairo::Color::DARK_OLIVE_GREEN.to_s)
  end

  # Dark orange: #FF8C00: (255, 140, 0)
  test("Dark orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 140, 0],
                 Cairo::Color::DARK_ORANGE.to_s)
  end

  # Dark orchid: #9932CC: (153, 50, 204)
  test("Dark orchid") do
    assert_equal("\#%02X%02X%02XFF" % [153, 50, 204],
                 Cairo::Color::DARK_ORCHID.to_s)
  end

  # Dark pastel blue: #779ECB: (119, 158, 203)
  test("Dark pastel blue") do
    assert_equal("\#%02X%02X%02XFF" % [119, 158, 203],
                 Cairo::Color::DARK_PASTEL_BLUE.to_s)
  end

  # Dark pastel green: #03C03C: (3, 192, 60)
  test("Dark pastel green") do
    assert_equal("\#%02X%02X%02XFF" % [3, 192, 60],
                 Cairo::Color::DARK_PASTEL_GREEN.to_s)
  end

  # Dark pastel purple: #966FD6: (150, 111, 214)
  test("Dark pastel purple") do
    assert_equal("\#%02X%02X%02XFF" % [150, 111, 214],
                 Cairo::Color::DARK_PASTEL_PURPLE.to_s)
  end

  # Dark pastel red: #C23B22: (194, 59, 34)
  test("Dark pastel red") do
    assert_equal("\#%02X%02X%02XFF" % [194, 59, 34],
                 Cairo::Color::DARK_PASTEL_RED.to_s)
  end

  # Dark pink: #E75480: (231, 84, 128)
  test("Dark pink") do
    assert_equal("\#%02X%02X%02XFF" % [231, 84, 128],
                 Cairo::Color::DARK_PINK.to_s)
  end

  # Dark powder blue: #003399: (0, 51, 153)
  test("Dark powder blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 51, 153],
                 Cairo::Color::DARK_POWDER_BLUE.to_s)
  end

  # Dark puce: #4F3A3C: (79, 58, 60)
  test("Dark puce") do
    assert_equal("\#%02X%02X%02XFF" % [79, 58, 60],
                 Cairo::Color::DARK_PUCE.to_s)
  end

  # Dark purple: #301934: (48, 25, 52)
  test("Dark purple") do
    assert_equal("\#%02X%02X%02XFF" % [48, 25, 52],
                 Cairo::Color::DARK_PURPLE.to_s)
  end

  # Dark raspberry: #872657: (135, 38, 87)
  test("Dark raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [135, 38, 87],
                 Cairo::Color::DARK_RASPBERRY.to_s)
  end

  # Dark red: #8B0000: (139, 0, 0)
  test("Dark red") do
    assert_equal("\#%02X%02X%02XFF" % [139, 0, 0],
                 Cairo::Color::DARK_RED.to_s)
  end

  # Dark salmon: #E9967A: (233, 150, 122)
  test("Dark salmon") do
    assert_equal("\#%02X%02X%02XFF" % [233, 150, 122],
                 Cairo::Color::DARK_SALMON.to_s)
  end

  # Dark scarlet: #560319: (86, 3, 25)
  test("Dark scarlet") do
    assert_equal("\#%02X%02X%02XFF" % [86, 3, 25],
                 Cairo::Color::DARK_SCARLET.to_s)
  end

  # Dark sea green: #8FBC8F: (143, 188, 143)
  test("Dark sea green") do
    assert_equal("\#%02X%02X%02XFF" % [143, 188, 143],
                 Cairo::Color::DARK_SEA_GREEN.to_s)
  end

  # Dark sienna: #3C1414: (60, 20, 20)
  test("Dark sienna") do
    assert_equal("\#%02X%02X%02XFF" % [60, 20, 20],
                 Cairo::Color::DARK_SIENNA.to_s)
  end

  # Dark silver: #71706E: (113, 112, 110)
  test("Dark silver") do
    assert_equal("\#%02X%02X%02XFF" % [113, 112, 110],
                 Cairo::Color::DARK_SILVER.to_s)
  end

  # Dark sky blue: #8CBED6: (140, 190, 214)
  test("Dark sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [140, 190, 214],
                 Cairo::Color::DARK_SKY_BLUE.to_s)
  end

  # Dark slate blue: #483D8B: (72, 61, 139)
  test("Dark slate blue") do
    assert_equal("\#%02X%02X%02XFF" % [72, 61, 139],
                 Cairo::Color::DARK_SLATE_BLUE.to_s)
  end

  # Dark slate gray: #2F4F4F: (47, 79, 79)
  test("Dark slate gray") do
    assert_equal("\#%02X%02X%02XFF" % [47, 79, 79],
                 Cairo::Color::DARK_SLATE_GRAY.to_s)
  end

  # Dark spring green: #177245: (23, 114, 69)
  test("Dark spring green") do
    assert_equal("\#%02X%02X%02XFF" % [23, 114, 69],
                 Cairo::Color::DARK_SPRING_GREEN.to_s)
  end

  # Dark tan: #918151: (145, 129, 81)
  test("Dark tan") do
    assert_equal("\#%02X%02X%02XFF" % [145, 129, 81],
                 Cairo::Color::DARK_TAN.to_s)
  end

  # Dark tangerine: #FFA812: (255, 168, 18)
  test("Dark tangerine") do
    assert_equal("\#%02X%02X%02XFF" % [255, 168, 18],
                 Cairo::Color::DARK_TANGERINE.to_s)
  end

  # Dark taupe: #483C32: (72, 60, 50)
  test("Dark taupe") do
    assert_equal("\#%02X%02X%02XFF" % [72, 60, 50],
                 Cairo::Color::DARK_TAUPE.to_s)
  end

  # Dark terra cotta: #CC4E5C: (204, 78, 92)
  test("Dark terra cotta") do
    assert_equal("\#%02X%02X%02XFF" % [204, 78, 92],
                 Cairo::Color::DARK_TERRA_COTTA.to_s)
  end

  # Dark turquoise: #00CED1: (0, 206, 209)
  test("Dark turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [0, 206, 209],
                 Cairo::Color::DARK_TURQUOISE.to_s)
  end

  # Dark vanilla: #D1BEA8: (209, 190, 168)
  test("Dark vanilla") do
    assert_equal("\#%02X%02X%02XFF" % [209, 190, 168],
                 Cairo::Color::DARK_VANILLA.to_s)
  end

  # Dark violet: #9400D3: (148, 0, 211)
  test("Dark violet") do
    assert_equal("\#%02X%02X%02XFF" % [148, 0, 211],
                 Cairo::Color::DARK_VIOLET.to_s)
  end

  # Dark yellow: #9B870C: (155, 135, 12)
  test("Dark yellow") do
    assert_equal("\#%02X%02X%02XFF" % [155, 135, 12],
                 Cairo::Color::DARK_YELLOW.to_s)
  end

  # Dartmouth green: #00703C: (0, 112, 60)
  test("Dartmouth green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 112, 60],
                 Cairo::Color::DARTMOUTH_GREEN.to_s)
  end

  # Davy's grey: #555555: (85, 85, 85)
  test("Davy's grey") do
    assert_equal("\#%02X%02X%02XFF" % [85, 85, 85],
                 Cairo::Color::DAVYS_GREY.to_s)
  end

  # Debian red: #D70A53: (215, 10, 83)
  test("Debian red") do
    assert_equal("\#%02X%02X%02XFF" % [215, 10, 83],
                 Cairo::Color::DEBIAN_RED.to_s)
  end

  # Deep amethyst: #9C8AA4: (156, 138, 164)
  test("Deep amethyst") do
    assert_equal("\#%02X%02X%02XFF" % [156, 138, 164],
                 Cairo::Color::DEEP_AMETHYST.to_s)
  end

  # Deep aquamarine: #40826D: (64, 130, 109)
  test("Deep aquamarine") do
    assert_equal("\#%02X%02X%02XFF" % [64, 130, 109],
                 Cairo::Color::DEEP_AQUAMARINE.to_s)
  end

  # Deep carmine: #A9203E: (169, 32, 62)
  test("Deep carmine") do
    assert_equal("\#%02X%02X%02XFF" % [169, 32, 62],
                 Cairo::Color::DEEP_CARMINE.to_s)
  end

  # Deep carmine pink: #EF3038: (239, 48, 56)
  test("Deep carmine pink") do
    assert_equal("\#%02X%02X%02XFF" % [239, 48, 56],
                 Cairo::Color::DEEP_CARMINE_PINK.to_s)
  end

  # Deep carrot orange: #E9692C: (233, 105, 44)
  test("Deep carrot orange") do
    assert_equal("\#%02X%02X%02XFF" % [233, 105, 44],
                 Cairo::Color::DEEP_CARROT_ORANGE.to_s)
  end

  # Deep cerise: #DA3287: (218, 50, 135)
  test("Deep cerise") do
    assert_equal("\#%02X%02X%02XFF" % [218, 50, 135],
                 Cairo::Color::DEEP_CERISE.to_s)
  end

  # Deep champagne: #FAD6A5: (250, 214, 165)
  test("Deep champagne") do
    assert_equal("\#%02X%02X%02XFF" % [250, 214, 165],
                 Cairo::Color::DEEP_CHAMPAGNE.to_s)
  end

  # Deep chestnut: #B94E48: (185, 78, 72)
  test("Deep chestnut") do
    assert_equal("\#%02X%02X%02XFF" % [185, 78, 72],
                 Cairo::Color::DEEP_CHESTNUT.to_s)
  end

  # Deep coffee: #704241: (112, 66, 65)
  test("Deep coffee") do
    assert_equal("\#%02X%02X%02XFF" % [112, 66, 65],
                 Cairo::Color::DEEP_COFFEE.to_s)
  end

  # Deep fuchsia: #C154C1: (193, 84, 193)
  test("Deep fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [193, 84, 193],
                 Cairo::Color::DEEP_FUCHSIA.to_s)
  end

  # Deep Green: #056608: (5, 102, 8)
  test("Deep Green") do
    assert_equal("\#%02X%02X%02XFF" % [5, 102, 8],
                 Cairo::Color::DEEP_GREEN.to_s)
  end

  # Deep green-cyan turquoise: #0E7C61: (14, 124, 97)
  test("Deep green-cyan turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [14, 124, 97],
                 Cairo::Color::DEEP_GREEN_CYAN_TURQUOISE.to_s)
  end

  # Deep jungle green: #004B49: (0, 75, 73)
  test("Deep jungle green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 75, 73],
                 Cairo::Color::DEEP_JUNGLE_GREEN.to_s)
  end

  # Deep koamaru: #333366: (51, 51, 102)
  test("Deep koamaru") do
    assert_equal("\#%02X%02X%02XFF" % [51, 51, 102],
                 Cairo::Color::DEEP_KOAMARU.to_s)
  end

  # Deep lemon: #F5C71A: (245, 199, 26)
  test("Deep lemon") do
    assert_equal("\#%02X%02X%02XFF" % [245, 199, 26],
                 Cairo::Color::DEEP_LEMON.to_s)
  end

  # Deep lilac: #9955BB: (153, 85, 187)
  test("Deep lilac") do
    assert_equal("\#%02X%02X%02XFF" % [153, 85, 187],
                 Cairo::Color::DEEP_LILAC.to_s)
  end

  # Deep magenta: #CC00CC: (204, 0, 204)
  test("Deep magenta") do
    assert_equal("\#%02X%02X%02XFF" % [204, 0, 204],
                 Cairo::Color::DEEP_MAGENTA.to_s)
  end

  # Deep maroon: #820000: (130, 0, 0)
  test("Deep maroon") do
    assert_equal("\#%02X%02X%02XFF" % [130, 0, 0],
                 Cairo::Color::DEEP_MAROON.to_s)
  end

  # Deep mauve: #D473D4: (212, 115, 212)
  test("Deep mauve") do
    assert_equal("\#%02X%02X%02XFF" % [212, 115, 212],
                 Cairo::Color::DEEP_MAUVE.to_s)
  end

  # Deep moss green: #355E3B: (53, 94, 59)
  test("Deep moss green") do
    assert_equal("\#%02X%02X%02XFF" % [53, 94, 59],
                 Cairo::Color::DEEP_MOSS_GREEN.to_s)
  end

  # Deep peach: #FFCBA4: (255, 203, 164)
  test("Deep peach") do
    assert_equal("\#%02X%02X%02XFF" % [255, 203, 164],
                 Cairo::Color::DEEP_PEACH.to_s)
  end

  # Deep pink: #FF1493: (255, 20, 147)
  test("Deep pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 20, 147],
                 Cairo::Color::DEEP_PINK.to_s)
  end

  # Deep puce: #A95C68: (169, 92, 104)
  test("Deep puce") do
    assert_equal("\#%02X%02X%02XFF" % [169, 92, 104],
                 Cairo::Color::DEEP_PUCE.to_s)
  end

  # Deep Red: #850101: (133, 1, 1)
  test("Deep Red") do
    assert_equal("\#%02X%02X%02XFF" % [133, 1, 1],
                 Cairo::Color::DEEP_RED.to_s)
  end

  # Deep ruby: #843F5B: (132, 63, 91)
  test("Deep ruby") do
    assert_equal("\#%02X%02X%02XFF" % [132, 63, 91],
                 Cairo::Color::DEEP_RUBY.to_s)
  end

  # Deep saffron: #FF9933: (255, 153, 51)
  test("Deep saffron") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 51],
                 Cairo::Color::DEEP_SAFFRON.to_s)
  end

  # Deep sky blue: #00BFFF: (0, 191, 255)
  test("Deep sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 191, 255],
                 Cairo::Color::DEEP_SKY_BLUE.to_s)
  end

  # Deep Space Sparkle: #4A646C: (74, 100, 108)
  test("Deep Space Sparkle") do
    assert_equal("\#%02X%02X%02XFF" % [74, 100, 108],
                 Cairo::Color::DEEP_SPACE_SPARKLE.to_s)
  end

  # Deep spring bud: #556B2F: (85, 107, 47)
  test("Deep spring bud") do
    assert_equal("\#%02X%02X%02XFF" % [85, 107, 47],
                 Cairo::Color::DEEP_SPRING_BUD.to_s)
  end

  # Deep Taupe: #7E5E60: (126, 94, 96)
  test("Deep Taupe") do
    assert_equal("\#%02X%02X%02XFF" % [126, 94, 96],
                 Cairo::Color::DEEP_TAUPE.to_s)
  end

  # Deep Tuscan red: #66424D: (102, 66, 77)
  test("Deep Tuscan red") do
    assert_equal("\#%02X%02X%02XFF" % [102, 66, 77],
                 Cairo::Color::DEEP_TUSCAN_RED.to_s)
  end

  # Deep violet: #330066: (51, 0, 102)
  test("Deep violet") do
    assert_equal("\#%02X%02X%02XFF" % [51, 0, 102],
                 Cairo::Color::DEEP_VIOLET.to_s)
  end

  # Deer: #BA8759: (186, 135, 89)
  test("Deer") do
    assert_equal("\#%02X%02X%02XFF" % [186, 135, 89],
                 Cairo::Color::DEER.to_s)
  end

  # Denim: #1560BD: (21, 96, 189)
  test("Denim") do
    assert_equal("\#%02X%02X%02XFF" % [21, 96, 189],
                 Cairo::Color::DENIM.to_s)
  end

  # Denim Blue: #2243B6: (34, 67, 182)
  test("Denim Blue") do
    assert_equal("\#%02X%02X%02XFF" % [34, 67, 182],
                 Cairo::Color::DENIM_BLUE.to_s)
  end

  # Desaturated cyan: #669999: (102, 153, 153)
  test("Desaturated cyan") do
    assert_equal("\#%02X%02X%02XFF" % [102, 153, 153],
                 Cairo::Color::DESATURATED_CYAN.to_s)
  end

  # Desert: #C19A6B: (193, 154, 107)
  test("Desert") do
    assert_equal("\#%02X%02X%02XFF" % [193, 154, 107],
                 Cairo::Color::DESERT.to_s)
  end

  # Desert sand: #EDC9AF: (237, 201, 175)
  test("Desert sand") do
    assert_equal("\#%02X%02X%02XFF" % [237, 201, 175],
                 Cairo::Color::DESERT_SAND.to_s)
  end

  # Desire: #EA3C53: (234, 60, 83)
  test("Desire") do
    assert_equal("\#%02X%02X%02XFF" % [234, 60, 83],
                 Cairo::Color::DESIRE.to_s)
  end

  # Diamond: #B9F2FF: (185, 242, 255)
  test("Diamond") do
    assert_equal("\#%02X%02X%02XFF" % [185, 242, 255],
                 Cairo::Color::DIAMOND.to_s)
  end

  # Dim gray: #696969: (105, 105, 105)
  test("Dim gray") do
    assert_equal("\#%02X%02X%02XFF" % [105, 105, 105],
                 Cairo::Color::DIM_GRAY.to_s)
  end

  # Dingy Dungeon: #C53151: (197, 49, 81)
  test("Dingy Dungeon") do
    assert_equal("\#%02X%02X%02XFF" % [197, 49, 81],
                 Cairo::Color::DINGY_DUNGEON.to_s)
  end

  # Dirt: #9B7653: (155, 118, 83)
  test("Dirt") do
    assert_equal("\#%02X%02X%02XFF" % [155, 118, 83],
                 Cairo::Color::DIRT.to_s)
  end

  # Dirty brown: #B5651E: (181, 101, 30)
  test("Dirty brown") do
    assert_equal("\#%02X%02X%02XFF" % [181, 101, 30],
                 Cairo::Color::DIRTY_BROWN.to_s)
  end

  # Dirty white: #E8E4C9: (232, 228, 201)
  test("Dirty white") do
    assert_equal("\#%02X%02X%02XFF" % [232, 228, 201],
                 Cairo::Color::DIRTY_WHITE.to_s)
  end

  # Dodger blue: #1E90FF: (30, 144, 255)
  test("Dodger blue") do
    assert_equal("\#%02X%02X%02XFF" % [30, 144, 255],
                 Cairo::Color::DODGER_BLUE.to_s)
  end

  # Dodie yellow: #FEF65B: (254, 246, 91)
  test("Dodie yellow") do
    assert_equal("\#%02X%02X%02XFF" % [254, 246, 91],
                 Cairo::Color::DODIE_YELLOW.to_s)
  end

  # Dogwood rose: #D71868: (215, 24, 104)
  test("Dogwood rose") do
    assert_equal("\#%02X%02X%02XFF" % [215, 24, 104],
                 Cairo::Color::DOGWOOD_ROSE.to_s)
  end

  # Dollar bill: #85BB65: (133, 187, 101)
  test("Dollar bill") do
    assert_equal("\#%02X%02X%02XFF" % [133, 187, 101],
                 Cairo::Color::DOLLAR_BILL.to_s)
  end

  # Dolphin gray: #828E84: (130, 142, 132)
  test("Dolphin gray") do
    assert_equal("\#%02X%02X%02XFF" % [130, 142, 132],
                 Cairo::Color::DOLPHIN_GRAY.to_s)
  end

  # Donkey brown: #664C28: (102, 76, 40)
  test("Donkey brown") do
    assert_equal("\#%02X%02X%02XFF" % [102, 76, 40],
                 Cairo::Color::DONKEY_BROWN.to_s)
  end

  # Drab: #967117: (150, 113, 23)
  test("Drab") do
    assert_equal("\#%02X%02X%02XFF" % [150, 113, 23],
                 Cairo::Color::DRAB.to_s)
  end

  # Duke blue: #00009C: (0, 0, 156)
  test("Duke blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 156],
                 Cairo::Color::DUKE_BLUE.to_s)
  end

  # Dust storm: #E5CCC9: (229, 204, 201)
  test("Dust storm") do
    assert_equal("\#%02X%02X%02XFF" % [229, 204, 201],
                 Cairo::Color::DUST_STORM.to_s)
  end

  # Dutch white: #EFDFBB: (239, 223, 187)
  test("Dutch white") do
    assert_equal("\#%02X%02X%02XFF" % [239, 223, 187],
                 Cairo::Color::DUTCH_WHITE.to_s)
  end

  # Earthtone: #5D3A1A: (93, 58, 26)
  test("Earthtone") do
    assert_equal("\#%02X%02X%02XFF" % [93, 58, 26],
                 Cairo::Color::EARTHTONE.to_s)
  end

  # Earth yellow: #E1A95F: (225, 169, 95)
  test("Earth yellow") do
    assert_equal("\#%02X%02X%02XFF" % [225, 169, 95],
                 Cairo::Color::EARTH_YELLOW.to_s)
  end

  # Ebony: #555D50: (85, 93, 80)
  test("Ebony") do
    assert_equal("\#%02X%02X%02XFF" % [85, 93, 80],
                 Cairo::Color::EBONY.to_s)
  end

  # Ecru: #C2B280: (194, 178, 128)
  test("Ecru") do
    assert_equal("\#%02X%02X%02XFF" % [194, 178, 128],
                 Cairo::Color::ECRU.to_s)
  end

  # Eerie black: #1B1B1B: (27, 27, 27)
  test("Eerie black") do
    assert_equal("\#%02X%02X%02XFF" % [27, 27, 27],
                 Cairo::Color::EERIE_BLACK.to_s)
  end

  # Eggplant: #614051: (97, 64, 81)
  test("Eggplant") do
    assert_equal("\#%02X%02X%02XFF" % [97, 64, 81],
                 Cairo::Color::EGGPLANT.to_s)
  end

  # Eggshell: #F0EAD6: (240, 234, 214)
  test("Eggshell") do
    assert_equal("\#%02X%02X%02XFF" % [240, 234, 214],
                 Cairo::Color::EGGSHELL.to_s)
  end

  # Egyptian blue: #1034A6: (16, 52, 166)
  test("Egyptian blue") do
    assert_equal("\#%02X%02X%02XFF" % [16, 52, 166],
                 Cairo::Color::EGYPTIAN_BLUE.to_s)
  end

  # Electric blue: #7DF9FF: (125, 249, 255)
  test("Electric blue") do
    assert_equal("\#%02X%02X%02XFF" % [125, 249, 255],
                 Cairo::Color::ELECTRIC_BLUE.to_s)
  end

  # Electric brown: #B56257: (181, 98, 87)
  test("Electric brown") do
    assert_equal("\#%02X%02X%02XFF" % [181, 98, 87],
                 Cairo::Color::ELECTRIC_BROWN.to_s)
  end

  # Electric crimson: #FF003F: (255, 0, 63)
  test("Electric crimson") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 63],
                 Cairo::Color::ELECTRIC_CRIMSON.to_s)
  end

  # Electric cyan: #00FFFF: (0, 255, 255)
  test("Electric cyan") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                 Cairo::Color::ELECTRIC_CYAN.to_s)
  end

  # Electric green: #00FF00: (0, 255, 0)
  test("Electric green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 0],
                 Cairo::Color::ELECTRIC_GREEN.to_s)
  end

  # Electric indigo: #6F00FF: (111, 0, 255)
  test("Electric indigo") do
    assert_equal("\#%02X%02X%02XFF" % [111, 0, 255],
                 Cairo::Color::ELECTRIC_INDIGO.to_s)
  end

  # Electric lavender: #F4BBFF: (244, 187, 255)
  test("Electric lavender") do
    assert_equal("\#%02X%02X%02XFF" % [244, 187, 255],
                 Cairo::Color::ELECTRIC_LAVENDER.to_s)
  end

  # Electric lime: #CCFF00: (204, 255, 0)
  test("Electric lime") do
    assert_equal("\#%02X%02X%02XFF" % [204, 255, 0],
                 Cairo::Color::ELECTRIC_LIME.to_s)
  end

  # Electric orange: #FF3503: (255, 53, 3)
  test("Electric orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 53, 3],
                 Cairo::Color::ELECTRIC_ORANGE.to_s)
  end

  # Electric pink: #F62681: (246, 38, 129)
  test("Electric pink") do
    assert_equal("\#%02X%02X%02XFF" % [246, 38, 129],
                 Cairo::Color::ELECTRIC_PINK.to_s)
  end

  # Electric purple: #BF00FF: (191, 0, 255)
  test("Electric purple") do
    assert_equal("\#%02X%02X%02XFF" % [191, 0, 255],
                 Cairo::Color::ELECTRIC_PURPLE.to_s)
  end

  # Electric red: #E60000: (230, 0, 0)
  test("Electric red") do
    assert_equal("\#%02X%02X%02XFF" % [230, 0, 0],
                 Cairo::Color::ELECTRIC_RED.to_s)
  end

  # Electric ultramarine: #3F00FF: (63, 0, 255)
  test("Electric ultramarine") do
    assert_equal("\#%02X%02X%02XFF" % [63, 0, 255],
                 Cairo::Color::ELECTRIC_ULTRAMARINE.to_s)
  end

  # Electric violet: #8F00FF: (143, 0, 255)
  test("Electric violet") do
    assert_equal("\#%02X%02X%02XFF" % [143, 0, 255],
                 Cairo::Color::ELECTRIC_VIOLET.to_s)
  end

  # Electric yellow: #FFFF33: (255, 255, 51)
  test("Electric yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 51],
                 Cairo::Color::ELECTRIC_YELLOW.to_s)
  end

  # Emerald: #50C878: (80, 200, 120)
  test("Emerald") do
    assert_equal("\#%02X%02X%02XFF" % [80, 200, 120],
                 Cairo::Color::EMERALD.to_s)
  end

  # Emerald green: #046307: (4, 99, 7)
  test("Emerald green") do
    assert_equal("\#%02X%02X%02XFF" % [4, 99, 7],
                 Cairo::Color::EMERALD_GREEN.to_s)
  end

  # Eminence: #6C3082: (108, 48, 130)
  test("Eminence") do
    assert_equal("\#%02X%02X%02XFF" % [108, 48, 130],
                 Cairo::Color::EMINENCE.to_s)
  end

  # English green: #1B4D3E: (27, 77, 62)
  test("English green") do
    assert_equal("\#%02X%02X%02XFF" % [27, 77, 62],
                 Cairo::Color::ENGLISH_GREEN.to_s)
  end

  # English lavender: #B48395: (180, 131, 149)
  test("English lavender") do
    assert_equal("\#%02X%02X%02XFF" % [180, 131, 149],
                 Cairo::Color::ENGLISH_LAVENDER.to_s)
  end

  # English red: #AB4B52: (171, 75, 82)
  test("English red") do
    assert_equal("\#%02X%02X%02XFF" % [171, 75, 82],
                 Cairo::Color::ENGLISH_RED.to_s)
  end

  # English vermillion: #CC474B: (204, 71, 75)
  test("English vermillion") do
    assert_equal("\#%02X%02X%02XFF" % [204, 71, 75],
                 Cairo::Color::ENGLISH_VERMILLION.to_s)
  end

  # English violet: #563C5C: (86, 60, 92)
  test("English violet") do
    assert_equal("\#%02X%02X%02XFF" % [86, 60, 92],
                 Cairo::Color::ENGLISH_VIOLET.to_s)
  end

  # Eton blue: #96C8A2: (150, 200, 162)
  test("Eton blue") do
    assert_equal("\#%02X%02X%02XFF" % [150, 200, 162],
                 Cairo::Color::ETON_BLUE.to_s)
  end

  # Eucalyptus: #44D7A8: (68, 215, 168)
  test("Eucalyptus") do
    assert_equal("\#%02X%02X%02XFF" % [68, 215, 168],
                 Cairo::Color::EUCALYPTUS.to_s)
  end

  # Facebook Blue: #39569C: (57, 86, 156)
  test("Facebook Blue") do
    assert_equal("\#%02X%02X%02XFF" % [57, 86, 156],
                 Cairo::Color::FACEBOOK_BLUE.to_s)
  end

  # Fallow: #C19A6B: (193, 154, 107)
  test("Fallow") do
    assert_equal("\#%02X%02X%02XFF" % [193, 154, 107],
                 Cairo::Color::FALLOW.to_s)
  end

  # Falu red: #801818: (128, 24, 24)
  test("Falu red") do
    assert_equal("\#%02X%02X%02XFF" % [128, 24, 24],
                 Cairo::Color::FALU_RED.to_s)
  end

  # Fandango: #B53389: (181, 51, 137)
  test("Fandango") do
    assert_equal("\#%02X%02X%02XFF" % [181, 51, 137],
                 Cairo::Color::FANDANGO.to_s)
  end

  # Fandango pink: #DE5285: (222, 82, 133)
  test("Fandango pink") do
    assert_equal("\#%02X%02X%02XFF" % [222, 82, 133],
                 Cairo::Color::FANDANGO_PINK.to_s)
  end

  # Fashion fuchsia: #F400A1: (244, 0, 161)
  test("Fashion fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [244, 0, 161],
                 Cairo::Color::FASHION_FUCHSIA.to_s)
  end

  # Fawn: #E5AA70: (229, 170, 112)
  test("Fawn") do
    assert_equal("\#%02X%02X%02XFF" % [229, 170, 112],
                 Cairo::Color::FAWN.to_s)
  end

  # Feldgrau: #4D5D53: (77, 93, 83)
  test("Feldgrau") do
    assert_equal("\#%02X%02X%02XFF" % [77, 93, 83],
                 Cairo::Color::FELDGRAU.to_s)
  end

  # Feldspar: #FDD5B1: (253, 213, 177)
  test("Feldspar") do
    assert_equal("\#%02X%02X%02XFF" % [253, 213, 177],
                 Cairo::Color::FELDSPAR.to_s)
  end

  # Fern green: #4F7942: (79, 121, 66)
  test("Fern green") do
    assert_equal("\#%02X%02X%02XFF" % [79, 121, 66],
                 Cairo::Color::FERN_GREEN.to_s)
  end

  # Ferrari red: #FF2800: (255, 40, 0)
  test("Ferrari red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 40, 0],
                 Cairo::Color::FERRARI_RED.to_s)
  end

  # Field drab: #6C541E: (108, 84, 30)
  test("Field drab") do
    assert_equal("\#%02X%02X%02XFF" % [108, 84, 30],
                 Cairo::Color::FIELD_DRAB.to_s)
  end

  # Fiery rose: #FF5470: (255, 84, 112)
  test("Fiery rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 84, 112],
                 Cairo::Color::FIERY_ROSE.to_s)
  end

  # Firebrick: #B22222: (178, 34, 34)
  test("Firebrick") do
    assert_equal("\#%02X%02X%02XFF" % [178, 34, 34],
                 Cairo::Color::FIREBRICK.to_s)
  end

  # Fire engine red: #CE2029: (206, 32, 41)
  test("Fire engine red") do
    assert_equal("\#%02X%02X%02XFF" % [206, 32, 41],
                 Cairo::Color::FIRE_ENGINE_RED.to_s)
  end

  # Fire opal: #E95C4B: (233, 92, 75)
  test("Fire opal") do
    assert_equal("\#%02X%02X%02XFF" % [233, 92, 75],
                 Cairo::Color::FIRE_OPAL.to_s)
  end

  # Flame: #E25822: (226, 88, 34)
  test("Flame") do
    assert_equal("\#%02X%02X%02XFF" % [226, 88, 34],
                 Cairo::Color::FLAME.to_s)
  end

  # Flamingo pink: #FC8EAC: (252, 142, 172)
  test("Flamingo pink") do
    assert_equal("\#%02X%02X%02XFF" % [252, 142, 172],
                 Cairo::Color::FLAMINGO_PINK.to_s)
  end

  # Flattery: #6B4423: (107, 68, 35)
  test("Flattery") do
    assert_equal("\#%02X%02X%02XFF" % [107, 68, 35],
                 Cairo::Color::FLATTERY.to_s)
  end

  # Flavescent: #F7E98E: (247, 233, 142)
  test("Flavescent") do
    assert_equal("\#%02X%02X%02XFF" % [247, 233, 142],
                 Cairo::Color::FLAVESCENT.to_s)
  end

  # Flax: #EEDC82: (238, 220, 130)
  test("Flax") do
    assert_equal("\#%02X%02X%02XFF" % [238, 220, 130],
                 Cairo::Color::FLAX.to_s)
  end

  # Flickr Blue: #216BD6: (33, 107, 214)
  test("Flickr Blue") do
    assert_equal("\#%02X%02X%02XFF" % [33, 107, 214],
                 Cairo::Color::FLICKR_BLUE.to_s)
  end

  # Flickr Pink: #FB0081: (251, 0, 129)
  test("Flickr Pink") do
    assert_equal("\#%02X%02X%02XFF" % [251, 0, 129],
                 Cairo::Color::FLICKR_PINK.to_s)
  end

  # Flirt: #A2006D: (162, 0, 109)
  test("Flirt") do
    assert_equal("\#%02X%02X%02XFF" % [162, 0, 109],
                 Cairo::Color::FLIRT.to_s)
  end

  # Floral white: #FFFAF0: (255, 250, 240)
  test("Floral white") do
    assert_equal("\#%02X%02X%02XFF" % [255, 250, 240],
                 Cairo::Color::FLORAL_WHITE.to_s)
  end

  # Flower girl: #F498AD: (244, 152, 173)
  test("Flower girl") do
    assert_equal("\#%02X%02X%02XFF" % [244, 152, 173],
                 Cairo::Color::FLOWER_GIRL.to_s)
  end

  # Fluorescent blue: #15F4EE: (21, 244, 238)
  test("Fluorescent blue") do
    assert_equal("\#%02X%02X%02XFF" % [21, 244, 238],
                 Cairo::Color::FLUORESCENT_BLUE.to_s)
  end

  # Fluorescent orange: #FFBF00: (255, 191, 0)
  test("Fluorescent orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 191, 0],
                 Cairo::Color::FLUORESCENT_ORANGE.to_s)
  end

  # Fluorescent pink: #FF1493: (255, 20, 147)
  test("Fluorescent pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 20, 147],
                 Cairo::Color::FLUORESCENT_PINK.to_s)
  end

  # Fluorescent yellow: #CCFF00: (204, 255, 0)
  test("Fluorescent yellow") do
    assert_equal("\#%02X%02X%02XFF" % [204, 255, 0],
                 Cairo::Color::FLUORESCENT_YELLOW.to_s)
  end

  # Folly: #FF004F: (255, 0, 79)
  test("Folly") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 79],
                 Cairo::Color::FOLLY.to_s)
  end

  # Forest green (Crayola): #5FA777: (95, 167, 119)
  test("Forest green (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [95, 167, 119],
                 Cairo::Color::FOREST_GREEN_CRAYOLA.to_s)
  end

  # Forest green (traditional): #014421: (1, 68, 33)
  test("Forest green (traditional)") do
    assert_equal("\#%02X%02X%02XFF" % [1, 68, 33],
                 Cairo::Color::FOREST_GREEN_TRADITIONAL.to_s)
  end

  # Forest green (web): #228B22: (34, 139, 34)
  test("Forest green (web)") do
    assert_equal("\#%02X%02X%02XFF" % [34, 139, 34],
                 Cairo::Color::FOREST_GREEN_WEB.to_s)
  end

  # French beige: #A67B5B: (166, 123, 91)
  test("French beige") do
    assert_equal("\#%02X%02X%02XFF" % [166, 123, 91],
                 Cairo::Color::FRENCH_BEIGE.to_s)
  end

  # French bistre: #856D4D: (133, 109, 77)
  test("French bistre") do
    assert_equal("\#%02X%02X%02XFF" % [133, 109, 77],
                 Cairo::Color::FRENCH_BISTRE.to_s)
  end

  # French blue: #0072BB: (0, 114, 187)
  test("French blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 114, 187],
                 Cairo::Color::FRENCH_BLUE.to_s)
  end

  # French fuchsia: #FD3F92: (253, 63, 146)
  test("French fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [253, 63, 146],
                 Cairo::Color::FRENCH_FUCHSIA.to_s)
  end

  # French lilac: #86608E: (134, 96, 142)
  test("French lilac") do
    assert_equal("\#%02X%02X%02XFF" % [134, 96, 142],
                 Cairo::Color::FRENCH_LILAC.to_s)
  end

  # French lime: #9EFD38: (158, 253, 56)
  test("French lime") do
    assert_equal("\#%02X%02X%02XFF" % [158, 253, 56],
                 Cairo::Color::FRENCH_LIME.to_s)
  end

  # French mauve: #D473D4: (212, 115, 212)
  test("French mauve") do
    assert_equal("\#%02X%02X%02XFF" % [212, 115, 212],
                 Cairo::Color::FRENCH_MAUVE.to_s)
  end

  # French Middle Red Purple: #1C0218: (28, 2, 24)
  test("French Middle Red Purple") do
    assert_equal("\#%02X%02X%02XFF" % [28, 2, 24],
                 Cairo::Color::FRENCH_MIDDLE_RED_PURPLE.to_s)
  end

  # French pink: #FD6C9E: (253, 108, 158)
  test("French pink") do
    assert_equal("\#%02X%02X%02XFF" % [253, 108, 158],
                 Cairo::Color::FRENCH_PINK.to_s)
  end

  # French plum: #811453: (129, 20, 83)
  test("French plum") do
    assert_equal("\#%02X%02X%02XFF" % [129, 20, 83],
                 Cairo::Color::FRENCH_PLUM.to_s)
  end

  # French puce: #4E1609: (78, 22, 9)
  test("French puce") do
    assert_equal("\#%02X%02X%02XFF" % [78, 22, 9],
                 Cairo::Color::FRENCH_PUCE.to_s)
  end

  # French raspberry: #C72C48: (199, 44, 72)
  test("French raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [199, 44, 72],
                 Cairo::Color::FRENCH_RASPBERRY.to_s)
  end

  # French rose: #F64A8A: (246, 74, 138)
  test("French rose") do
    assert_equal("\#%02X%02X%02XFF" % [246, 74, 138],
                 Cairo::Color::FRENCH_ROSE.to_s)
  end

  # French sky blue: #77B5FE: (119, 181, 254)
  test("French sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [119, 181, 254],
                 Cairo::Color::FRENCH_SKY_BLUE.to_s)
  end

  # French violet: #8806CE: (136, 6, 206)
  test("French violet") do
    assert_equal("\#%02X%02X%02XFF" % [136, 6, 206],
                 Cairo::Color::FRENCH_VIOLET.to_s)
  end

  # French wine: #AC1E44: (172, 30, 68)
  test("French wine") do
    assert_equal("\#%02X%02X%02XFF" % [172, 30, 68],
                 Cairo::Color::FRENCH_WINE.to_s)
  end

  # Fresh Air: #A6E7FF: (166, 231, 255)
  test("Fresh Air") do
    assert_equal("\#%02X%02X%02XFF" % [166, 231, 255],
                 Cairo::Color::FRESH_AIR.to_s)
  end

  # Frostbite: #E936A7: (233, 54, 167)
  test("Frostbite") do
    assert_equal("\#%02X%02X%02XFF" % [233, 54, 167],
                 Cairo::Color::FROSTBITE.to_s)
  end

  # Fuchsia: #FF00FF: (255, 0, 255)
  test("Fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 255],
                 Cairo::Color::FUCHSIA.to_s)
  end

  # Fuchsia (Crayola): #C154C1: (193, 84, 193)
  test("Fuchsia (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [193, 84, 193],
                 Cairo::Color::FUCHSIA_CRAYOLA.to_s)
  end

  # Fuchsia pink: #FF77FF: (255, 119, 255)
  test("Fuchsia pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 119, 255],
                 Cairo::Color::FUCHSIA_PINK.to_s)
  end

  # Fuchsia purple: #CC397B: (204, 57, 123)
  test("Fuchsia purple") do
    assert_equal("\#%02X%02X%02XFF" % [204, 57, 123],
                 Cairo::Color::FUCHSIA_PURPLE.to_s)
  end

  # Fuchsia rose: #C74375: (199, 67, 117)
  test("Fuchsia rose") do
    assert_equal("\#%02X%02X%02XFF" % [199, 67, 117],
                 Cairo::Color::FUCHSIA_ROSE.to_s)
  end

  # Fulvous: #E48400: (228, 132, 0)
  test("Fulvous") do
    assert_equal("\#%02X%02X%02XFF" % [228, 132, 0],
                 Cairo::Color::FULVOUS.to_s)
  end

  # Fuzzy Wuzzy: #CC6666: (204, 102, 102)
  test("Fuzzy Wuzzy") do
    assert_equal("\#%02X%02X%02XFF" % [204, 102, 102],
                 Cairo::Color::FUZZY_WUZZY.to_s)
  end

  # Gainsboro: #DCDCDC: (220, 220, 220)
  test("Gainsboro") do
    assert_equal("\#%02X%02X%02XFF" % [220, 220, 220],
                 Cairo::Color::GAINSBORO.to_s)
  end

  # Gamboge: #E49B0F: (228, 155, 15)
  test("Gamboge") do
    assert_equal("\#%02X%02X%02XFF" % [228, 155, 15],
                 Cairo::Color::GAMBOGE.to_s)
  end

  # Gamboge orange (brown): #996600: (152, 102, 0)
  test("Gamboge orange (brown)") do
    assert_equal("\#%02X%02X%02XFF" % [152, 102, 0],
                 Cairo::Color::GAMBOGE_ORANGE_BROWN.to_s)
  end

  # Garnet: #733635: (115, 54, 53)
  test("Garnet") do
    assert_equal("\#%02X%02X%02XFF" % [115, 54, 53],
                 Cairo::Color::GARNET.to_s)
  end

  # Gargoyle Gas: #FFDF46: (255, 223, 70)
  test("Gargoyle Gas") do
    assert_equal("\#%02X%02X%02XFF" % [255, 223, 70],
                 Cairo::Color::GARGOYLE_GAS.to_s)
  end

  # Generic viridian: #007F66: (0, 127, 102)
  test("Generic viridian") do
    assert_equal("\#%02X%02X%02XFF" % [0, 127, 102],
                 Cairo::Color::GENERIC_VIRIDIAN.to_s)
  end

  # Ghost white: #F8F8FF: (248, 248, 255)
  test("Ghost white") do
    assert_equal("\#%02X%02X%02XFF" % [248, 248, 255],
                 Cairo::Color::GHOST_WHITE.to_s)
  end

  # Giant's Club: #B05C52: (176, 92, 82)
  test("Giant's Club") do
    assert_equal("\#%02X%02X%02XFF" % [176, 92, 82],
                 Cairo::Color::GIANTS_CLUB.to_s)
  end

  # Giants orange: #FE5A1D: (254, 90, 29)
  test("Giants orange") do
    assert_equal("\#%02X%02X%02XFF" % [254, 90, 29],
                 Cairo::Color::GIANTS_ORANGE.to_s)
  end

  # Gin: #D8E4BC: (216, 228, 188)
  test("Gin") do
    assert_equal("\#%02X%02X%02XFF" % [216, 228, 188],
                 Cairo::Color::GIN.to_s)
  end

  # Glaucous: #6082B6: (96, 130, 182)
  test("Glaucous") do
    assert_equal("\#%02X%02X%02XFF" % [96, 130, 182],
                 Cairo::Color::GLAUCOUS.to_s)
  end

  # Glossy grape: #AB92B3: (171, 146, 179)
  test("Glossy grape") do
    assert_equal("\#%02X%02X%02XFF" % [171, 146, 179],
                 Cairo::Color::GLOSSY_GRAPE.to_s)
  end

  # GO green: #00AB66: (0, 171, 102)
  test("GO green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 171, 102],
                 Cairo::Color::GO_GREEN.to_s)
  end

  # Gold: #A57C00: (165, 124, 0)
  test("Gold") do
    assert_equal("\#%02X%02X%02XFF" % [165, 124, 0],
                 Cairo::Color::GOLD.to_s)
  end

  # Gold (metallic): #D4AF37: (212, 175, 55)
  test("Gold (metallic)") do
    assert_equal("\#%02X%02X%02XFF" % [212, 175, 55],
                 Cairo::Color::GOLD_METALLIC.to_s)
  end

  # Gold (web) (Golden): #FFD700: (255, 215, 0)
  test("Gold (web) (Golden)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 215, 0],
                 Cairo::Color::GOLD_WEB_GOLDEN.to_s)
  end

  # Gold (Crayola): #E6BE8A: (230, 190, 138)
  test("Gold (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [230, 190, 138],
                 Cairo::Color::GOLD_CRAYOLA.to_s)
  end

  # Gold Fusion: #85754E: (133, 117, 78)
  test("Gold Fusion") do
    assert_equal("\#%02X%02X%02XFF" % [133, 117, 78],
                 Cairo::Color::GOLD_FUSION.to_s)
  end

  # Gold foil: #BD9B16: (189, 155, 22)
  test("Gold foil") do
    assert_equal("\#%02X%02X%02XFF" % [189, 155, 22],
                 Cairo::Color::GOLD_FOIL.to_s)
  end

  # Golden brown: #996515: (153, 101, 21)
  test("Golden brown") do
    assert_equal("\#%02X%02X%02XFF" % [153, 101, 21],
                 Cairo::Color::GOLDEN_BROWN.to_s)
  end

  # Golden poppy: #FCC200: (252, 194, 0)
  test("Golden poppy") do
    assert_equal("\#%02X%02X%02XFF" % [252, 194, 0],
                 Cairo::Color::GOLDEN_POPPY.to_s)
  end

  # Golden yellow: #FFDF00: (255, 223, 0)
  test("Golden yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 223, 0],
                 Cairo::Color::GOLDEN_YELLOW.to_s)
  end

  # Goldenrod: #DAA520: (218, 165, 32)
  test("Goldenrod") do
    assert_equal("\#%02X%02X%02XFF" % [218, 165, 32],
                 Cairo::Color::GOLDENROD.to_s)
  end

  # Google Chrome red: #DE5246: (222, 82, 70)
  test("Google Chrome red") do
    assert_equal("\#%02X%02X%02XFF" % [222, 82, 70],
                 Cairo::Color::GOOGLE_CHROME_RED.to_s)
  end

  # Google Chrome blue: #4C8BF5: (76, 139, 245)
  test("Google Chrome blue") do
    assert_equal("\#%02X%02X%02XFF" % [76, 139, 245],
                 Cairo::Color::GOOGLE_CHROME_BLUE.to_s)
  end

  # Google Chrome green: #1AA260: (26, 162, 96)
  test("Google Chrome green") do
    assert_equal("\#%02X%02X%02XFF" % [26, 162, 96],
                 Cairo::Color::GOOGLE_CHROME_GREEN.to_s)
  end

  # Google Chrome yellow: #FFCE44: (255, 206, 68)
  test("Google Chrome yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 206, 68],
                 Cairo::Color::GOOGLE_CHROME_YELLOW.to_s)
  end

  # Granite gray: #676767: (103, 103, 103)
  test("Granite gray") do
    assert_equal("\#%02X%02X%02XFF" % [103, 103, 103],
                 Cairo::Color::GRANITE_GRAY.to_s)
  end

  # Granny Smith apple: #A8E4A0: (168, 228, 160)
  test("Granny Smith apple") do
    assert_equal("\#%02X%02X%02XFF" % [168, 228, 160],
                 Cairo::Color::GRANNY_SMITH_APPLE.to_s)
  end

  # Grape: #6F2DA8: (111, 45, 168)
  test("Grape") do
    assert_equal("\#%02X%02X%02XFF" % [111, 45, 168],
                 Cairo::Color::GRAPE.to_s)
  end

  # Gray (HTML/CSS gray): #808080: (128, 128, 128)
  test("Gray (HTML/CSS gray)") do
    assert_equal("\#%02X%02X%02XFF" % [128, 128, 128],
                 Cairo::Color::GRAY_HTML_CSS_GRAY.to_s)
  end

  # Gray (X11 gray): #BEBEBE: (190, 190, 190)
  test("Gray (X11 gray)") do
    assert_equal("\#%02X%02X%02XFF" % [190, 190, 190],
                 Cairo::Color::GRAY_X11_GRAY.to_s)
  end

  # Gray-asparagus: #465945: (70, 89, 69)
  test("Gray-asparagus") do
    assert_equal("\#%02X%02X%02XFF" % [70, 89, 69],
                 Cairo::Color::GRAY_ASPARAGUS.to_s)
  end

  # Gray-blue: #8C92AC: (140, 146, 172)
  test("Gray-blue") do
    assert_equal("\#%02X%02X%02XFF" % [140, 146, 172],
                 Cairo::Color::GRAY_BLUE.to_s)
  end

  # Green: #008001: (0, 128, 1)
  test("Green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 128, 1],
                 Cairo::Color::GREEN.to_s)
  end

  # Green (Color Wheel) (X11 green): #00FF00: (0, 255, 0)
  test("Green (Color Wheel) (X11 green)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 0],
                 Cairo::Color::GREEN_COLOR_WHEEL_X11_GREEN.to_s)
  end

  # Green (Crayola): #1CAC78: (28, 172, 120)
  test("Green (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [28, 172, 120],
                 Cairo::Color::GREEN_CRAYOLA.to_s)
  end

  # Green (HTML/CSS color): #008000: (0, 128, 0)
  test("Green (HTML/CSS color)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 128, 0],
                 Cairo::Color::GREEN_HTML_CSS_COLOR.to_s)
  end

  # Green (Munsell): #00A877: (0, 168, 119)
  test("Green (Munsell)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 168, 119],
                 Cairo::Color::GREEN_MUNSELL.to_s)
  end

  # Green (NCS): #009F6B: (0, 159, 107)
  test("Green (NCS)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 159, 107],
                 Cairo::Color::GREEN_NCS.to_s)
  end

  # Green (Pantone): #00AD43: (0, 173, 67)
  test("Green (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 173, 67],
                 Cairo::Color::GREEN_PANTONE.to_s)
  end

  # Green (pigment): #00A550: (0, 165, 80)
  test("Green (pigment)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 165, 80],
                 Cairo::Color::GREEN_PIGMENT.to_s)
  end

  # Green (RYB): #66B032: (102, 176, 50)
  test("Green (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [102, 176, 50],
                 Cairo::Color::GREEN_RYB.to_s)
  end

  # Green-blue: #1164B4: (17, 100, 180)
  test("Green-blue") do
    assert_equal("\#%02X%02X%02XFF" % [17, 100, 180],
                 Cairo::Color::GREEN_BLUE.to_s)
  end

  # Green-blue (Crayola): #2887C8: (40, 135, 200)
  test("Green-blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [40, 135, 200],
                 Cairo::Color::GREEN_BLUE_CRAYOLA.to_s)
  end

  # Green Cola: #4C721D: (76, 114, 29)
  test("Green Cola") do
    assert_equal("\#%02X%02X%02XFF" % [76, 114, 29],
                 Cairo::Color::GREEN_COLA.to_s)
  end

  # Green-cyan: #009966: (0, 153, 102)
  test("Green-cyan") do
    assert_equal("\#%02X%02X%02XFF" % [0, 153, 102],
                 Cairo::Color::GREEN_CYAN.to_s)
  end

  # Green Lizard: #A7F432: (167, 244, 50)
  test("Green Lizard") do
    assert_equal("\#%02X%02X%02XFF" % [167, 244, 50],
                 Cairo::Color::GREEN_LIZARD.to_s)
  end

  # Green Sheen: #6EAEA1: (110, 174, 161)
  test("Green Sheen") do
    assert_equal("\#%02X%02X%02XFF" % [110, 174, 161],
                 Cairo::Color::GREEN_SHEEN.to_s)
  end

  # Green slime: #65FF00: (101, 255, 0)
  test("Green slime") do
    assert_equal("\#%02X%02X%02XFF" % [101, 255, 0],
                 Cairo::Color::GREEN_SLIME.to_s)
  end

  # Green-yellow: #ADFF2F: (173, 255, 47)
  test("Green-yellow") do
    assert_equal("\#%02X%02X%02XFF" % [173, 255, 47],
                 Cairo::Color::GREEN_YELLOW.to_s)
  end

  # Green-yellow (Crayola): #F0E891: (240, 232, 145)
  test("Green-yellow (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [240, 232, 145],
                 Cairo::Color::GREEN_YELLOW_CRAYOLA.to_s)
  end

  # Grullo: #A99A86: (169, 154, 134)
  test("Grullo") do
    assert_equal("\#%02X%02X%02XFF" % [169, 154, 134],
                 Cairo::Color::GRULLO.to_s)
  end

  # Guppie green: #00FF7F: (0, 255, 127)
  test("Guppie green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 127],
                 Cairo::Color::GUPPIE_GREEN.to_s)
  end

  # Gunmetal: #2a3439: (42, 52, 57)
  test("Gunmetal") do
    assert_equal("\#%02X%02X%02XFF" % [42, 52, 57],
                 Cairo::Color::GUNMETAL.to_s)
  end

  # Guyabano: #F8F8F8: (248, 248, 248)
  test("Guyabano") do
    assert_equal("\#%02X%02X%02XFF" % [248, 248, 248],
                 Cairo::Color::GUYABANO.to_s)
  end

  # Halayà úbe: #663854: (102, 55, 84)
  test("Halay\u00E0 \u00FAbe") do
    assert_equal("\#%02X%02X%02XFF" % [102, 55, 84],
                 Cairo::Color::HALAYA_UBE.to_s)
  end

  # Halloween orange: #EB6123: (235, 97, 35)
  test("Halloween orange") do
    assert_equal("\#%02X%02X%02XFF" % [235, 97, 35],
                 Cairo::Color::HALLOWEEN_ORANGE.to_s)
  end

  # Han blue: #446CCF: (68, 108, 207)
  test("Han blue") do
    assert_equal("\#%02X%02X%02XFF" % [68, 108, 207],
                 Cairo::Color::HAN_BLUE.to_s)
  end

  # Han purple: #5218FA: (82, 24, 250)
  test("Han purple") do
    assert_equal("\#%02X%02X%02XFF" % [82, 24, 250],
                 Cairo::Color::HAN_PURPLE.to_s)
  end

  # Hansa yellow: #E9D66B: (233, 214, 107)
  test("Hansa yellow") do
    assert_equal("\#%02X%02X%02XFF" % [233, 214, 107],
                 Cairo::Color::HANSA_YELLOW.to_s)
  end

  # Harlequin: #3FFF00: (63, 255, 0)
  test("Harlequin") do
    assert_equal("\#%02X%02X%02XFF" % [63, 255, 0],
                 Cairo::Color::HARLEQUIN.to_s)
  end

  # Harlequin green: #46CB18: (70, 203, 24)
  test("Harlequin green") do
    assert_equal("\#%02X%02X%02XFF" % [70, 203, 24],
                 Cairo::Color::HARLEQUIN_GREEN.to_s)
  end

  # Harmonious rose: #F29CB7: (242, 156, 183)
  test("Harmonious rose") do
    assert_equal("\#%02X%02X%02XFF" % [242, 156, 183],
                 Cairo::Color::HARMONIOUS_ROSE.to_s)
  end

  # Harvard crimson: #C90016: (201, 0, 22)
  test("Harvard crimson") do
    assert_equal("\#%02X%02X%02XFF" % [201, 0, 22],
                 Cairo::Color::HARVARD_CRIMSON.to_s)
  end

  # Harvest gold: #DA9100: (218, 145, 0)
  test("Harvest gold") do
    assert_equal("\#%02X%02X%02XFF" % [218, 145, 0],
                 Cairo::Color::HARVEST_GOLD.to_s)
  end

  # Heart gold: #808000: (128, 128, 0)
  test("Heart gold") do
    assert_equal("\#%02X%02X%02XFF" % [128, 128, 0],
                 Cairo::Color::HEART_GOLD.to_s)
  end

  # Heat Wave: #FF7A00: (255, 122, 0)
  test("Heat Wave") do
    assert_equal("\#%02X%02X%02XFF" % [255, 122, 0],
                 Cairo::Color::HEAT_WAVE.to_s)
  end

  # Heidelberg red: #960018: (150, 0, 24)
  test("Heidelberg red") do
    assert_equal("\#%02X%02X%02XFF" % [150, 0, 24],
                 Cairo::Color::HEIDELBERG_RED.to_s)
  end

  # Heliotrope: #DF73FF: (223, 115, 255)
  test("Heliotrope") do
    assert_equal("\#%02X%02X%02XFF" % [223, 115, 255],
                 Cairo::Color::HELIOTROPE.to_s)
  end

  # Heliotrope gray: #AA98A9: (170, 152, 168)
  test("Heliotrope gray") do
    assert_equal("\#%02X%02X%02XFF" % [170, 152, 168],
                 Cairo::Color::HELIOTROPE_GRAY.to_s)
  end

  # Heliotrope magenta: #AA00BB: (170, 0, 187)
  test("Heliotrope magenta") do
    assert_equal("\#%02X%02X%02XFF" % [170, 0, 187],
                 Cairo::Color::HELIOTROPE_MAGENTA.to_s)
  end

  # Hollywood cerise: #F400A1: (244, 0, 161)
  test("Hollywood cerise") do
    assert_equal("\#%02X%02X%02XFF" % [244, 0, 161],
                 Cairo::Color::HOLLYWOOD_CERISE.to_s)
  end

  # Honeydew: #F0FFF0: (240, 255, 240)
  test("Honeydew") do
    assert_equal("\#%02X%02X%02XFF" % [240, 255, 240],
                 Cairo::Color::HONEYDEW.to_s)
  end

  # Honolulu blue: #006DB0: (0, 109, 176)
  test("Honolulu blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 109, 176],
                 Cairo::Color::HONOLULU_BLUE.to_s)
  end

  # Hooker's green: #49796B: (73, 121, 107)
  test("Hooker's green") do
    assert_equal("\#%02X%02X%02XFF" % [73, 121, 107],
                 Cairo::Color::HOOKERS_GREEN.to_s)
  end

  # Hot magenta: #FF1DCE: (255, 29, 206)
  test("Hot magenta") do
    assert_equal("\#%02X%02X%02XFF" % [255, 29, 206],
                 Cairo::Color::HOT_MAGENTA.to_s)
  end

  # Hot pink: #FF69B4: (255, 105, 180)
  test("Hot pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 105, 180],
                 Cairo::Color::HOT_PINK.to_s)
  end

  # Hunter green: #355E3B: (53, 94, 59)
  test("Hunter green") do
    assert_equal("\#%02X%02X%02XFF" % [53, 94, 59],
                 Cairo::Color::HUNTER_GREEN.to_s)
  end

  # Iceberg: #71A6D2: (113, 166, 210)
  test("Iceberg") do
    assert_equal("\#%02X%02X%02XFF" % [113, 166, 210],
                 Cairo::Color::ICEBERG.to_s)
  end

  # Iced tea: #923C01: (146, 60, 1)
  test("Iced tea") do
    assert_equal("\#%02X%02X%02XFF" % [146, 60, 1],
                 Cairo::Color::ICED_TEA.to_s)
  end

  # Icterine: #FCF75E: (252, 247, 94)
  test("Icterine") do
    assert_equal("\#%02X%02X%02XFF" % [252, 247, 94],
                 Cairo::Color::ICTERINE.to_s)
  end

  # Iguana green: #71BC78: (113, 188, 120)
  test("Iguana green") do
    assert_equal("\#%02X%02X%02XFF" % [113, 188, 120],
                 Cairo::Color::IGUANA_GREEN.to_s)
  end

  # Illuminating emerald: #319177: (49, 145, 119)
  test("Illuminating emerald") do
    assert_equal("\#%02X%02X%02XFF" % [49, 145, 119],
                 Cairo::Color::ILLUMINATING_EMERALD.to_s)
  end

  # Imperial: #602F6B: (96, 47, 107)
  test("Imperial") do
    assert_equal("\#%02X%02X%02XFF" % [96, 47, 107],
                 Cairo::Color::IMPERIAL.to_s)
  end

  # Imperial blue: #002395: (0, 35, 149)
  test("Imperial blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 35, 149],
                 Cairo::Color::IMPERIAL_BLUE.to_s)
  end

  # Imperial purple: #66023C: (102, 2, 60)
  test("Imperial purple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 2, 60],
                 Cairo::Color::IMPERIAL_PURPLE.to_s)
  end

  # Imperial red: #ED2939: (237, 41, 57)
  test("Imperial red") do
    assert_equal("\#%02X%02X%02XFF" % [237, 41, 57],
                 Cairo::Color::IMPERIAL_RED.to_s)
  end

  # Inchworm: #B2EC5D: (178, 236, 93)
  test("Inchworm") do
    assert_equal("\#%02X%02X%02XFF" % [178, 236, 93],
                 Cairo::Color::INCHWORM.to_s)
  end

  # Independence: #4C516D: (76, 81, 109)
  test("Independence") do
    assert_equal("\#%02X%02X%02XFF" % [76, 81, 109],
                 Cairo::Color::INDEPENDENCE.to_s)
  end

  # India green: #138808: (19, 136, 8)
  test("India green") do
    assert_equal("\#%02X%02X%02XFF" % [19, 136, 8],
                 Cairo::Color::INDIA_GREEN.to_s)
  end

  # Indian red: #CD5C5C: (205, 92, 92)
  test("Indian red") do
    assert_equal("\#%02X%02X%02XFF" % [205, 92, 92],
                 Cairo::Color::INDIAN_RED.to_s)
  end

  # Indian yellow: #E3A857: (227, 168, 87)
  test("Indian yellow") do
    assert_equal("\#%02X%02X%02XFF" % [227, 168, 87],
                 Cairo::Color::INDIAN_YELLOW.to_s)
  end

  # Indigo: #4B0082: (75, 0, 130)
  test("Indigo") do
    assert_equal("\#%02X%02X%02XFF" % [75, 0, 130],
                 Cairo::Color::INDIGO.to_s)
  end

  # Indigo dye: #091F92: (9, 31, 146)
  test("Indigo dye") do
    assert_equal("\#%02X%02X%02XFF" % [9, 31, 146],
                 Cairo::Color::INDIGO_DYE.to_s)
  end

  # Indigo (Crayola): #4F69C6: (79, 105, 198)
  test("Indigo (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [79, 105, 198],
                 Cairo::Color::INDIGO_CRAYOLA.to_s)
  end

  # Indigo (Rainbow): #233067: (35, 48, 103)
  test("Indigo (Rainbow)") do
    assert_equal("\#%02X%02X%02XFF" % [35, 48, 103],
                 Cairo::Color::INDIGO_RAINBOW.to_s)
  end

  # Indigo (web): #4B0082: (75, 0, 130)
  test("Indigo (web)") do
    assert_equal("\#%02X%02X%02XFF" % [75, 0, 130],
                 Cairo::Color::INDIGO_WEB.to_s)
  end

  # Infra red: #FF496C: (255, 73, 108)
  test("Infra red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 73, 108],
                 Cairo::Color::INFRA_RED.to_s)
  end

  # Interdimensional blue: #360CCC: (54, 12, 204)
  test("Interdimensional blue") do
    assert_equal("\#%02X%02X%02XFF" % [54, 12, 204],
                 Cairo::Color::INTERDIMENSIONAL_BLUE.to_s)
  end

  # International Klein Blue: #002FA7: (0, 47, 167)
  test("International Klein Blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 47, 167],
                 Cairo::Color::INTERNATIONAL_KLEIN_BLUE.to_s)
  end

  # International orange (aerospace): #FF4F00: (255, 79, 0)
  test("International orange (aerospace)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 79, 0],
                 Cairo::Color::INTERNATIONAL_ORANGE_AEROSPACE.to_s)
  end

  # International orange (engineering): #BA160C: (186, 22, 12)
  test("International orange (engineering)") do
    assert_equal("\#%02X%02X%02XFF" % [186, 22, 12],
                 Cairo::Color::INTERNATIONAL_ORANGE_ENGINEERING.to_s)
  end

  # International orange (Golden Gate Bridge): #C0362C: (192, 54, 44)
  test("International orange (Golden Gate Bridge)") do
    assert_equal("\#%02X%02X%02XFF" % [192, 54, 44],
                 Cairo::Color::INTERNATIONAL_ORANGE_GOLDEN_GATE_BRIDGE.to_s)
  end

  # Iris: #5A4FCF: (90, 79, 207)
  test("Iris") do
    assert_equal("\#%02X%02X%02XFF" % [90, 79, 207],
                 Cairo::Color::IRIS.to_s)
  end

  # Iron: #A19D94: (161, 157, 148)
  test("Iron") do
    assert_equal("\#%02X%02X%02XFF" % [161, 157, 148],
                 Cairo::Color::IRON.to_s)
  end

  # Irresistible: #B3446C: (179, 68, 108)
  test("Irresistible") do
    assert_equal("\#%02X%02X%02XFF" % [179, 68, 108],
                 Cairo::Color::IRRESISTIBLE.to_s)
  end

  # Isabelline: #F4F0EC: (244, 240, 236)
  test("Isabelline") do
    assert_equal("\#%02X%02X%02XFF" % [244, 240, 236],
                 Cairo::Color::ISABELLINE.to_s)
  end

  # Islamic green: #009000: (0, 144, 0)
  test("Islamic green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 144, 0],
                 Cairo::Color::ISLAMIC_GREEN.to_s)
  end

  # Italian sky blue: #B2FFFF: (178, 255, 255)
  test("Italian sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [178, 255, 255],
                 Cairo::Color::ITALIAN_SKY_BLUE.to_s)
  end

  # Ivory: #FFFFF0: (255, 255, 240)
  test("Ivory") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 240],
                 Cairo::Color::IVORY.to_s)
  end

  # Jacarta: #3D325D: (61, 50, 93)
  test("Jacarta") do
    assert_equal("\#%02X%02X%02XFF" % [61, 50, 93],
                 Cairo::Color::JACARTA.to_s)
  end

  # Jacko bean: #413628: (65, 54, 40)
  test("Jacko bean") do
    assert_equal("\#%02X%02X%02XFF" % [65, 54, 40],
                 Cairo::Color::JACKO_BEAN.to_s)
  end

  # Jade: #00A86B: (0, 168, 107)
  test("Jade") do
    assert_equal("\#%02X%02X%02XFF" % [0, 168, 107],
                 Cairo::Color::JADE.to_s)
  end

  # Japanese carmine: #9D2933: (157, 41, 51)
  test("Japanese carmine") do
    assert_equal("\#%02X%02X%02XFF" % [157, 41, 51],
                 Cairo::Color::JAPANESE_CARMINE.to_s)
  end

  # Japanese indigo: #264348: (38, 67, 72)
  test("Japanese indigo") do
    assert_equal("\#%02X%02X%02XFF" % [38, 67, 72],
                 Cairo::Color::JAPANESE_INDIGO.to_s)
  end

  # Japanese laurel: #2F7532: (47, 117, 50)
  test("Japanese laurel") do
    assert_equal("\#%02X%02X%02XFF" % [47, 117, 50],
                 Cairo::Color::JAPANESE_LAUREL.to_s)
  end

  # Japanese violet: #5B3256: (91, 50, 86)
  test("Japanese violet") do
    assert_equal("\#%02X%02X%02XFF" % [91, 50, 86],
                 Cairo::Color::JAPANESE_VIOLET.to_s)
  end

  # Jasmine: #F8DE7E: (248, 222, 126)
  test("Jasmine") do
    assert_equal("\#%02X%02X%02XFF" % [248, 222, 126],
                 Cairo::Color::JASMINE.to_s)
  end

  # Jasper: #D73B3E: (215, 59, 62)
  test("Jasper") do
    assert_equal("\#%02X%02X%02XFF" % [215, 59, 62],
                 Cairo::Color::JASPER.to_s)
  end

  # Jasper orange: #DE8F4E: (223, 145, 79)
  test("Jasper orange") do
    assert_equal("\#%02X%02X%02XFF" % [223, 145, 79],
                 Cairo::Color::JASPER_ORANGE.to_s)
  end

  # Jazzberry jam: #A50B5E: (165, 11, 94)
  test("Jazzberry jam") do
    assert_equal("\#%02X%02X%02XFF" % [165, 11, 94],
                 Cairo::Color::JAZZBERRY_JAM.to_s)
  end

  # Jelly bean: #DA614E: (218, 97, 78)
  test("Jelly bean") do
    assert_equal("\#%02X%02X%02XFF" % [218, 97, 78],
                 Cairo::Color::JELLY_BEAN.to_s)
  end

  # Jelly bean blue: #44798E: (68, 121, 142)
  test("Jelly bean blue") do
    assert_equal("\#%02X%02X%02XFF" % [68, 121, 142],
                 Cairo::Color::JELLY_BEAN_BLUE.to_s)
  end

  # Jet: #343434: (52, 52, 52)
  test("Jet") do
    assert_equal("\#%02X%02X%02XFF" % [52, 52, 52],
                 Cairo::Color::JET.to_s)
  end

  # Jet stream: #BBD0C9: (187, 208, 201)
  test("Jet stream") do
    assert_equal("\#%02X%02X%02XFF" % [187, 208, 201],
                 Cairo::Color::JET_STREAM.to_s)
  end

  # Jonquil: #F4CA16: (244, 202, 22)
  test("Jonquil") do
    assert_equal("\#%02X%02X%02XFF" % [244, 202, 22],
                 Cairo::Color::JONQUIL.to_s)
  end

  # Jordy blue: #8AB9F1: (138, 185, 241)
  test("Jordy blue") do
    assert_equal("\#%02X%02X%02XFF" % [138, 185, 241],
                 Cairo::Color::JORDY_BLUE.to_s)
  end

  # June bud: #BDDA57: (189, 218, 87)
  test("June bud") do
    assert_equal("\#%02X%02X%02XFF" % [189, 218, 87],
                 Cairo::Color::JUNE_BUD.to_s)
  end

  # Jungle green: #29AB87: (41, 171, 135)
  test("Jungle green") do
    assert_equal("\#%02X%02X%02XFF" % [41, 171, 135],
                 Cairo::Color::JUNGLE_GREEN.to_s)
  end

  # Kelly green: #4CBB17: (76, 187, 23)
  test("Kelly green") do
    assert_equal("\#%02X%02X%02XFF" % [76, 187, 23],
                 Cairo::Color::KELLY_GREEN.to_s)
  end

  # Kenyan copper: #7C1C05: (124, 28, 5)
  test("Kenyan copper") do
    assert_equal("\#%02X%02X%02XFF" % [124, 28, 5],
                 Cairo::Color::KENYAN_COPPER.to_s)
  end

  # Keppel: #3AB09E: (58, 176, 158)
  test("Keppel") do
    assert_equal("\#%02X%02X%02XFF" % [58, 176, 158],
                 Cairo::Color::KEPPEL.to_s)
  end

  # Key lime: #E8F48C: (232, 244, 140)
  test("Key lime") do
    assert_equal("\#%02X%02X%02XFF" % [232, 244, 140],
                 Cairo::Color::KEY_LIME.to_s)
  end

  # Khaki: #C3B091: (195, 176, 145)
  test("Khaki") do
    assert_equal("\#%02X%02X%02XFF" % [195, 176, 145],
                 Cairo::Color::KHAKI.to_s)
  end

  # Khaki (X11): #F0E68C: (240, 230, 140)
  test("Khaki (X11)") do
    assert_equal("\#%02X%02X%02XFF" % [240, 230, 140],
                 Cairo::Color::KHAKI_X11.to_s)
  end

  # Kiwi: #8EE53F: (142, 229, 63)
  test("Kiwi") do
    assert_equal("\#%02X%02X%02XFF" % [142, 229, 63],
                 Cairo::Color::KIWI.to_s)
  end

  # Kobe: #882D17: (136, 45, 23)
  test("Kobe") do
    assert_equal("\#%02X%02X%02XFF" % [136, 45, 23],
                 Cairo::Color::KOBE.to_s)
  end

  # Kobi: #E79FC4: (231, 159, 196)
  test("Kobi") do
    assert_equal("\#%02X%02X%02XFF" % [231, 159, 196],
                 Cairo::Color::KOBI.to_s)
  end

  # Kobicha: #6B4423: (107, 68, 35)
  test("Kobicha") do
    assert_equal("\#%02X%02X%02XFF" % [107, 68, 35],
                 Cairo::Color::KOBICHA.to_s)
  end

  # Kombu green: #354230: (53, 66, 48)
  test("Kombu green") do
    assert_equal("\#%02X%02X%02XFF" % [53, 66, 48],
                 Cairo::Color::KOMBU_GREEN.to_s)
  end

  # KSU Purple: #512888: (79, 38, 131)
  test("KSU Purple") do
    assert_equal("\#%02X%02X%02XFF" % [79, 38, 131],
                 Cairo::Color::KSU_PURPLE.to_s)
  end

  # KU Crimson: #E8000D: (232, 0, 13)
  test("KU Crimson") do
    assert_equal("\#%02X%02X%02XFF" % [232, 0, 13],
                 Cairo::Color::KU_CRIMSON.to_s)
  end

  # La Salle green: #087830: (8, 120, 48)
  test("La Salle green") do
    assert_equal("\#%02X%02X%02XFF" % [8, 120, 48],
                 Cairo::Color::LA_SALLE_GREEN.to_s)
  end

  # Languid lavender: #D6CADD: (214, 202, 221)
  test("Languid lavender") do
    assert_equal("\#%02X%02X%02XFF" % [214, 202, 221],
                 Cairo::Color::LANGUID_LAVENDER.to_s)
  end

  # Lanzones: #E0BC5B: (224, 188, 91)
  test("Lanzones") do
    assert_equal("\#%02X%02X%02XFF" % [224, 188, 91],
                 Cairo::Color::LANZONES.to_s)
  end

  # Lapis lazuli: #26619C: (38, 97, 156)
  test("Lapis lazuli") do
    assert_equal("\#%02X%02X%02XFF" % [38, 97, 156],
                 Cairo::Color::LAPIS_LAZULI.to_s)
  end

  # Laser Lemon: #FFFF66: (255, 255, 102)
  test("Laser Lemon") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 102],
                 Cairo::Color::LASER_LEMON.to_s)
  end

  # Laurel green: #A9BA9D: (169, 186, 157)
  test("Laurel green") do
    assert_equal("\#%02X%02X%02XFF" % [169, 186, 157],
                 Cairo::Color::LAUREL_GREEN.to_s)
  end

  # Lava: #CF1020: (207, 16, 32)
  test("Lava") do
    assert_equal("\#%02X%02X%02XFF" % [207, 16, 32],
                 Cairo::Color::LAVA.to_s)
  end

  # Lavender: #B57EDC: (181, 126, 220)
  test("Lavender") do
    assert_equal("\#%02X%02X%02XFF" % [181, 126, 220],
                 Cairo::Color::LAVENDER.to_s)
  end

  # Lavender (web): #E6E6FA: (230, 230, 250)
  test("Lavender (web)") do
    assert_equal("\#%02X%02X%02XFF" % [230, 230, 250],
                 Cairo::Color::LAVENDER_WEB.to_s)
  end

  # Lavender blue: #CCCCFF: (204, 204, 255)
  test("Lavender blue") do
    assert_equal("\#%02X%02X%02XFF" % [204, 204, 255],
                 Cairo::Color::LAVENDER_BLUE.to_s)
  end

  # Lavender blush: #FFF0F5: (255, 240, 245)
  test("Lavender blush") do
    assert_equal("\#%02X%02X%02XFF" % [255, 240, 245],
                 Cairo::Color::LAVENDER_BLUSH.to_s)
  end

  # Lavender gray: #C4C3D0: (196, 195, 208)
  test("Lavender gray") do
    assert_equal("\#%02X%02X%02XFF" % [196, 195, 208],
                 Cairo::Color::LAVENDER_GRAY.to_s)
  end

  # Lavender indigo: #9457EB: (148, 87, 235)
  test("Lavender indigo") do
    assert_equal("\#%02X%02X%02XFF" % [148, 87, 235],
                 Cairo::Color::LAVENDER_INDIGO.to_s)
  end

  # Lavender magenta: #EE82EE: (238, 130, 238)
  test("Lavender magenta") do
    assert_equal("\#%02X%02X%02XFF" % [238, 130, 238],
                 Cairo::Color::LAVENDER_MAGENTA.to_s)
  end

  # Lavender mist: #E6E6FA: (230, 230, 250)
  test("Lavender mist") do
    assert_equal("\#%02X%02X%02XFF" % [230, 230, 250],
                 Cairo::Color::LAVENDER_MIST.to_s)
  end

  # Lavender pink: #FBAED2: (251, 174, 210)
  test("Lavender pink") do
    assert_equal("\#%02X%02X%02XFF" % [251, 174, 210],
                 Cairo::Color::LAVENDER_PINK.to_s)
  end

  # Lavender purple: #967BB6: (150, 123, 182)
  test("Lavender purple") do
    assert_equal("\#%02X%02X%02XFF" % [150, 123, 182],
                 Cairo::Color::LAVENDER_PURPLE.to_s)
  end

  # Lavender rose: #FBA0E3: (251, 160, 227)
  test("Lavender rose") do
    assert_equal("\#%02X%02X%02XFF" % [251, 160, 227],
                 Cairo::Color::LAVENDER_ROSE.to_s)
  end

  # Lawn green: #7CFC00: (124, 252, 0)
  test("Lawn green") do
    assert_equal("\#%02X%02X%02XFF" % [124, 252, 0],
                 Cairo::Color::LAWN_GREEN.to_s)
  end

  # Lemon: #FFF700: (255, 247, 0)
  test("Lemon") do
    assert_equal("\#%02X%02X%02XFF" % [255, 247, 0],
                 Cairo::Color::LEMON.to_s)
  end

  # Lemon chiffon: #FFFACD: (255, 250, 205)
  test("Lemon chiffon") do
    assert_equal("\#%02X%02X%02XFF" % [255, 250, 205],
                 Cairo::Color::LEMON_CHIFFON.to_s)
  end

  # Lemon curry: #CCA01D: (204, 160, 29)
  test("Lemon curry") do
    assert_equal("\#%02X%02X%02XFF" % [204, 160, 29],
                 Cairo::Color::LEMON_CURRY.to_s)
  end

  # Lemon glacier: #FDFF00: (253, 255, 0)
  test("Lemon glacier") do
    assert_equal("\#%02X%02X%02XFF" % [253, 255, 0],
                 Cairo::Color::LEMON_GLACIER.to_s)
  end

  # Lemon iced tea: #BD3000: (189, 48, 0)
  test("Lemon iced tea") do
    assert_equal("\#%02X%02X%02XFF" % [189, 48, 0],
                 Cairo::Color::LEMON_ICED_TEA.to_s)
  end

  # Lemon lime: #E3FF00: (227, 255, 0)
  test("Lemon lime") do
    assert_equal("\#%02X%02X%02XFF" % [227, 255, 0],
                 Cairo::Color::LEMON_LIME.to_s)
  end

  # Lemon meringue: #F6EABE: (246, 234, 190)
  test("Lemon meringue") do
    assert_equal("\#%02X%02X%02XFF" % [246, 234, 190],
                 Cairo::Color::LEMON_MERINGUE.to_s)
  end

  # Lemon yellow: #FFF44F: (255, 244, 79)
  test("Lemon yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 244, 79],
                 Cairo::Color::LEMON_YELLOW.to_s)
  end

  # Lemon yellow (Crayola): #FFFF9F: (255, 255, 159)
  test("Lemon yellow (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 159],
                 Cairo::Color::LEMON_YELLOW_CRAYOLA.to_s)
  end

  # Lenurple: #BA93D8: (186, 147, 216)
  test("Lenurple") do
    assert_equal("\#%02X%02X%02XFF" % [186, 147, 216],
                 Cairo::Color::LENURPLE.to_s)
  end

  # Liberty: #545AA7: (84, 90, 167)
  test("Liberty") do
    assert_equal("\#%02X%02X%02XFF" % [84, 90, 167],
                 Cairo::Color::LIBERTY.to_s)
  end

  # Licorice: #1A1110: (26, 17, 16)
  test("Licorice") do
    assert_equal("\#%02X%02X%02XFF" % [26, 17, 16],
                 Cairo::Color::LICORICE.to_s)
  end

  # Light apricot: #FDD5B1: (253, 213, 177)
  test("Light apricot") do
    assert_equal("\#%02X%02X%02XFF" % [253, 213, 177],
                 Cairo::Color::LIGHT_APRICOT.to_s)
  end

  # Light blue: #ADD8E6: (173, 216, 230)
  test("Light blue") do
    assert_equal("\#%02X%02X%02XFF" % [173, 216, 230],
                 Cairo::Color::LIGHT_BLUE.to_s)
  end

  # Light brown: #B5651D: (181, 101, 29)
  test("Light brown") do
    assert_equal("\#%02X%02X%02XFF" % [181, 101, 29],
                 Cairo::Color::LIGHT_BROWN.to_s)
  end

  # Light carmine pink: #E66771: (230, 103, 113)
  test("Light carmine pink") do
    assert_equal("\#%02X%02X%02XFF" % [230, 103, 113],
                 Cairo::Color::LIGHT_CARMINE_PINK.to_s)
  end

  # Light chocolate cosmos: #551F2F: (85, 31, 47)
  test("Light chocolate cosmos") do
    assert_equal("\#%02X%02X%02XFF" % [85, 31, 47],
                 Cairo::Color::LIGHT_CHOCOLATE_COSMOS.to_s)
  end

  # Light cobalt blue: #88ACE0: (136, 172, 224)
  test("Light cobalt blue") do
    assert_equal("\#%02X%02X%02XFF" % [136, 172, 224],
                 Cairo::Color::LIGHT_COBALT_BLUE.to_s)
  end

  # Light coral: #F08080: (240, 128, 128)
  test("Light coral") do
    assert_equal("\#%02X%02X%02XFF" % [240, 128, 128],
                 Cairo::Color::LIGHT_CORAL.to_s)
  end

  # Light cornflower blue: #93CCEA: (147, 204, 234)
  test("Light cornflower blue") do
    assert_equal("\#%02X%02X%02XFF" % [147, 204, 234],
                 Cairo::Color::LIGHT_CORNFLOWER_BLUE.to_s)
  end

  # Light crimson: #F56991: (245, 105, 145)
  test("Light crimson") do
    assert_equal("\#%02X%02X%02XFF" % [245, 105, 145],
                 Cairo::Color::LIGHT_CRIMSON.to_s)
  end

  # Light cyan: #E0FFFF: (224, 255, 255)
  test("Light cyan") do
    assert_equal("\#%02X%02X%02XFF" % [224, 255, 255],
                 Cairo::Color::LIGHT_CYAN.to_s)
  end

  # Light deep pink: #FF5CCD: (255, 92, 205)
  test("Light deep pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 92, 205],
                 Cairo::Color::LIGHT_DEEP_PINK.to_s)
  end

  # Light French beige: #C8AD7F: (200, 173, 127)
  test("Light French beige") do
    assert_equal("\#%02X%02X%02XFF" % [200, 173, 127],
                 Cairo::Color::LIGHT_FRENCH_BEIGE.to_s)
  end

  # Light fuchsia pink: #F984EF: (249, 132, 239)
  test("Light fuchsia pink") do
    assert_equal("\#%02X%02X%02XFF" % [249, 132, 239],
                 Cairo::Color::LIGHT_FUCHSIA_PINK.to_s)
  end

  # Light gold: #B29700: (178, 151, 0)
  test("Light gold") do
    assert_equal("\#%02X%02X%02XFF" % [178, 151, 0],
                 Cairo::Color::LIGHT_GOLD.to_s)
  end

  # Light goldenrod: #FFEC8B: (255, 236, 139)
  test("Light goldenrod") do
    assert_equal("\#%02X%02X%02XFF" % [255, 236, 139],
                 Cairo::Color::LIGHT_GOLDENROD.to_s)
  end

  # Light goldenrod yellow: #FAFAD2: (250, 250, 210)
  test("Light goldenrod yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 250, 210],
                 Cairo::Color::LIGHT_GOLDENROD_YELLOW.to_s)
  end

  # Light gray: #D3D3D3: (211, 211, 211)
  test("Light gray") do
    assert_equal("\#%02X%02X%02XFF" % [211, 211, 211],
                 Cairo::Color::LIGHT_GRAY.to_s)
  end

  # Light grayish magenta: #CC99CC: (204, 153, 204)
  test("Light grayish magenta") do
    assert_equal("\#%02X%02X%02XFF" % [204, 153, 204],
                 Cairo::Color::LIGHT_GRAYISH_MAGENTA.to_s)
  end

  # Light green: #90EE90: (144, 238, 144)
  test("Light green") do
    assert_equal("\#%02X%02X%02XFF" % [144, 238, 144],
                 Cairo::Color::LIGHT_GREEN.to_s)
  end

  # Light hot pink: #FFB3DE: (255, 179, 222)
  test("Light hot pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 179, 222],
                 Cairo::Color::LIGHT_HOT_PINK.to_s)
  end

  # Light khaki: #F0E68C: (240, 230, 140)
  test("Light khaki") do
    assert_equal("\#%02X%02X%02XFF" % [240, 230, 140],
                 Cairo::Color::LIGHT_KHAKI.to_s)
  end

  # Light medium orchid: #D39BCB: (211, 155, 203)
  test("Light medium orchid") do
    assert_equal("\#%02X%02X%02XFF" % [211, 155, 203],
                 Cairo::Color::LIGHT_MEDIUM_ORCHID.to_s)
  end

  # Light moss green: #ADDFAD: (173, 223, 173)
  test("Light moss green") do
    assert_equal("\#%02X%02X%02XFF" % [173, 223, 173],
                 Cairo::Color::LIGHT_MOSS_GREEN.to_s)
  end

  # Light mustard: #FF3333: (238, 221, 98)
  test("Light mustard") do
    assert_equal("\#%02X%02X%02XFF" % [238, 221, 98],
                 Cairo::Color::LIGHT_MUSTARD.to_s)
  end

  # Light orange: #FED8B1: (254, 216, 177)
  test("Light orange") do
    assert_equal("\#%02X%02X%02XFF" % [254, 216, 177],
                 Cairo::Color::LIGHT_ORANGE.to_s)
  end

  # Light orchid: #E6A8D7: (230, 168, 215)
  test("Light orchid") do
    assert_equal("\#%02X%02X%02XFF" % [230, 168, 215],
                 Cairo::Color::LIGHT_ORCHID.to_s)
  end

  # Light pastel purple: #B19CD9: (177, 156, 217)
  test("Light pastel purple") do
    assert_equal("\#%02X%02X%02XFF" % [177, 156, 217],
                 Cairo::Color::LIGHT_PASTEL_PURPLE.to_s)
  end

  # Light periwinkle: #C5CBE1: (197, 203, 225)
  test("Light periwinkle") do
    assert_equal("\#%02X%02X%02XFF" % [197, 203, 225],
                 Cairo::Color::LIGHT_PERIWINKLE.to_s)
  end

  # Light pink: #FFB6C1: (255, 182, 193)
  test("Light pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 182, 193],
                 Cairo::Color::LIGHT_PINK.to_s)
  end

  # Light red: #FF3333: (255, 51, 51)
  test("Light red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 51, 51],
                 Cairo::Color::LIGHT_RED.to_s)
  end

  # Light red ochre: #E97451: (233, 116, 81)
  test("Light red ochre") do
    assert_equal("\#%02X%02X%02XFF" % [233, 116, 81],
                 Cairo::Color::LIGHT_RED_OCHRE.to_s)
  end

  # Light salmon: #FFA07A: (255, 160, 122)
  test("Light salmon") do
    assert_equal("\#%02X%02X%02XFF" % [255, 160, 122],
                 Cairo::Color::LIGHT_SALMON.to_s)
  end

  # Light salmon pink: #FF9999: (255, 153, 153)
  test("Light salmon pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 153],
                 Cairo::Color::LIGHT_SALMON_PINK.to_s)
  end

  # Light sea green: #20B2AA: (32, 178, 170)
  test("Light sea green") do
    assert_equal("\#%02X%02X%02XFF" % [32, 178, 170],
                 Cairo::Color::LIGHT_SEA_GREEN.to_s)
  end

  # Light silver: #D8D8D8: (216, 216, 216)
  test("Light silver") do
    assert_equal("\#%02X%02X%02XFF" % [216, 216, 216],
                 Cairo::Color::LIGHT_SILVER.to_s)
  end

  # Light sky blue: #87CEFA: (135, 206, 250)
  test("Light sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [135, 206, 250],
                 Cairo::Color::LIGHT_SKY_BLUE.to_s)
  end

  # Light slate gray: #778899: (119, 136, 153)
  test("Light slate gray") do
    assert_equal("\#%02X%02X%02XFF" % [119, 136, 153],
                 Cairo::Color::LIGHT_SLATE_GRAY.to_s)
  end

  # Light steel blue: #B0C4DE: (176, 196, 222)
  test("Light steel blue") do
    assert_equal("\#%02X%02X%02XFF" % [176, 196, 222],
                 Cairo::Color::LIGHT_STEEL_BLUE.to_s)
  end

  # Light taupe: #B38B6D: (179, 139, 109)
  test("Light taupe") do
    assert_equal("\#%02X%02X%02XFF" % [179, 139, 109],
                 Cairo::Color::LIGHT_TAUPE.to_s)
  end

  # Light Thulian pink: #E68FAC: (230, 143, 172)
  test("Light Thulian pink") do
    assert_equal("\#%02X%02X%02XFF" % [230, 143, 172],
                 Cairo::Color::LIGHT_THULIAN_PINK.to_s)
  end

  # Light turquoise: #AFE4DE: (175, 228, 222)
  test("Light turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [175, 228, 222],
                 Cairo::Color::LIGHT_TURQUOISE.to_s)
  end

  # Light violet: #7A5299: (122, 82, 153)
  test("Light violet") do
    assert_equal("\#%02X%02X%02XFF" % [122, 82, 153],
                 Cairo::Color::LIGHT_VIOLET.to_s)
  end

  # Light yellow: #FFFFE0: (255, 255, 224)
  test("Light yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 224],
                 Cairo::Color::LIGHT_YELLOW.to_s)
  end

  # Lilac: #C8A2C8: (200, 162, 200)
  test("Lilac") do
    assert_equal("\#%02X%02X%02XFF" % [200, 162, 200],
                 Cairo::Color::LILAC.to_s)
  end

  # Lilac Luster: #AE98AA: (174, 152, 170)
  test("Lilac Luster") do
    assert_equal("\#%02X%02X%02XFF" % [174, 152, 170],
                 Cairo::Color::LILAC_LUSTER.to_s)
  end

  # Lime (color wheel): #BFFF00: (191, 255, 0)
  test("Lime (color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [191, 255, 0],
                 Cairo::Color::LIME_COLOR_WHEEL.to_s)
  end

  # Lime (web) (X11 green): #00FF00: (0, 255, 0)
  test("Lime (web) (X11 green)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 0],
                 Cairo::Color::LIME_WEB_X11_GREEN.to_s)
  end

  # Lime green: #32CD32: (50, 205, 50)
  test("Lime green") do
    assert_equal("\#%02X%02X%02XFF" % [50, 205, 50],
                 Cairo::Color::LIME_GREEN.to_s)
  end

  # Limerick: #9DC209: (157, 194, 9)
  test("Limerick") do
    assert_equal("\#%02X%02X%02XFF" % [157, 194, 9],
                 Cairo::Color::LIMERICK.to_s)
  end

  # Lincoln green: #195905: (25, 89, 5)
  test("Lincoln green") do
    assert_equal("\#%02X%02X%02XFF" % [25, 89, 5],
                 Cairo::Color::LINCOLN_GREEN.to_s)
  end

  # Linen: #FAF0E6: (250, 240, 230)
  test("Linen") do
    assert_equal("\#%02X%02X%02XFF" % [250, 240, 230],
                 Cairo::Color::LINEN.to_s)
  end

  # Lion: #C19A6B: (193, 154, 107)
  test("Lion") do
    assert_equal("\#%02X%02X%02XFF" % [193, 154, 107],
                 Cairo::Color::LION.to_s)
  end

  # Liseran purple: #DE6FA1: (222, 111, 161)
  test("Liseran purple") do
    assert_equal("\#%02X%02X%02XFF" % [222, 111, 161],
                 Cairo::Color::LISERAN_PURPLE.to_s)
  end

  # Little boy blue: #6CA0DC: (108, 160, 220)
  test("Little boy blue") do
    assert_equal("\#%02X%02X%02XFF" % [108, 160, 220],
                 Cairo::Color::LITTLE_BOY_BLUE.to_s)
  end

  # Little girl pink: #F8B9D4: (248, 185, 212)
  test("Little girl pink") do
    assert_equal("\#%02X%02X%02XFF" % [248, 185, 212],
                 Cairo::Color::LITTLE_GIRL_PINK.to_s)
  end

  # Liver: #674C47: (103, 76, 71)
  test("Liver") do
    assert_equal("\#%02X%02X%02XFF" % [103, 76, 71],
                 Cairo::Color::LIVER.to_s)
  end

  # Liver (dogs): #B86D29: (184, 109, 41)
  test("Liver (dogs)") do
    assert_equal("\#%02X%02X%02XFF" % [184, 109, 41],
                 Cairo::Color::LIVER_DOGS.to_s)
  end

  # Liver (organ): #6C2E1F: (108, 46, 31)
  test("Liver (organ)") do
    assert_equal("\#%02X%02X%02XFF" % [108, 46, 31],
                 Cairo::Color::LIVER_ORGAN.to_s)
  end

  # Liver chestnut: #987456: (152, 116, 86)
  test("Liver chestnut") do
    assert_equal("\#%02X%02X%02XFF" % [152, 116, 86],
                 Cairo::Color::LIVER_CHESTNUT.to_s)
  end

  # Livid: #6699CC: (102, 153, 204)
  test("Livid") do
    assert_equal("\#%02X%02X%02XFF" % [102, 153, 204],
                 Cairo::Color::LIVID.to_s)
  end

  # Lotion: #FEFDFA: (255, 254, 250)
  test("Lotion") do
    assert_equal("\#%02X%02X%02XFF" % [255, 254, 250],
                 Cairo::Color::LOTION.to_s)
  end

  # Lotion blue: #15F2FD: (123, 154, 200)
  test("Lotion blue") do
    assert_equal("\#%02X%02X%02XFF" % [123, 154, 200],
                 Cairo::Color::LOTION_BLUE.to_s)
  end

  # Lotion pink: #ECCFCF: (236, 207, 207)
  test("Lotion pink") do
    assert_equal("\#%02X%02X%02XFF" % [236, 207, 207],
                 Cairo::Color::LOTION_PINK.to_s)
  end

  # Lumber: #FFE4CD: (255, 228, 205)
  test("Lumber") do
    assert_equal("\#%02X%02X%02XFF" % [255, 228, 205],
                 Cairo::Color::LUMBER.to_s)
  end

  # Lust: #E62020: (230, 32, 32)
  test("Lust") do
    assert_equal("\#%02X%02X%02XFF" % [230, 32, 32],
                 Cairo::Color::LUST.to_s)
  end

  # Maastricht Blue: #001C3D: (0, 28, 61)
  test("Maastricht Blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 28, 61],
                 Cairo::Color::MAASTRICHT_BLUE.to_s)
  end

  # Macaroni and Cheese: #FFBD88: (255, 189, 136)
  test("Macaroni and Cheese") do
    assert_equal("\#%02X%02X%02XFF" % [255, 189, 136],
                 Cairo::Color::MACARONI_AND_CHEESE.to_s)
  end

  # Madder Lake: #CC3336: (204, 51, 54)
  test("Madder Lake") do
    assert_equal("\#%02X%02X%02XFF" % [204, 51, 54],
                 Cairo::Color::MADDER_LAKE.to_s)
  end

  # Magenta: #FF00FF: (255, 0, 255)
  test("Magenta") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 255],
                 Cairo::Color::MAGENTA.to_s)
  end

  # Mahogany: #C04000: (192, 64, 0)
  test("Mahogany") do
    assert_equal("\#%02X%02X%02XFF" % [192, 64, 0],
                 Cairo::Color::MAHOGANY.to_s)
  end

  # Maize: #FBEC5D: (251, 236, 93)
  test("Maize") do
    assert_equal("\#%02X%02X%02XFF" % [251, 236, 93],
                 Cairo::Color::MAIZE.to_s)
  end

  # Maize (Crayola): #F2C649: (242, 198, 73)
  test("Maize (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [242, 198, 73],
                 Cairo::Color::MAIZE_CRAYOLA.to_s)
  end

  # Majorelle Blue: #6050DC: (96, 80, 220)
  test("Majorelle Blue") do
    assert_equal("\#%02X%02X%02XFF" % [96, 80, 220],
                 Cairo::Color::MAJORELLE_BLUE.to_s)
  end

  # Malachite: #0BDA51: (11, 218, 81)
  test("Malachite") do
    assert_equal("\#%02X%02X%02XFF" % [11, 218, 81],
                 Cairo::Color::MALACHITE.to_s)
  end

  # Manatee: #979AAA: (151, 154, 170)
  test("Manatee") do
    assert_equal("\#%02X%02X%02XFF" % [151, 154, 170],
                 Cairo::Color::MANATEE.to_s)
  end

  # Mandarin: #F37A48: (243, 122, 72)
  test("Mandarin") do
    assert_equal("\#%02X%02X%02XFF" % [243, 122, 72],
                 Cairo::Color::MANDARIN.to_s)
  end

  # Mango: #FDBE02: (253, 190, 2)
  test("Mango") do
    assert_equal("\#%02X%02X%02XFF" % [253, 190, 2],
                 Cairo::Color::MANGO.to_s)
  end

  # Mango green: #96FF00: (150, 255, 0)
  test("Mango green") do
    assert_equal("\#%02X%02X%02XFF" % [150, 255, 0],
                 Cairo::Color::MANGO_GREEN.to_s)
  end

  # Mango Tango: #FF8243: (255, 130, 67)
  test("Mango Tango") do
    assert_equal("\#%02X%02X%02XFF" % [255, 130, 67],
                 Cairo::Color::MANGO_TANGO.to_s)
  end

  # Mantis: #74C365: (116, 195, 101)
  test("Mantis") do
    assert_equal("\#%02X%02X%02XFF" % [116, 195, 101],
                 Cairo::Color::MANTIS.to_s)
  end

  # Mardi Gras: #880085: (136, 0, 133)
  test("Mardi Gras") do
    assert_equal("\#%02X%02X%02XFF" % [136, 0, 133],
                 Cairo::Color::MARDI_GRAS.to_s)
  end

  # Marigold: #EAA221: (234, 162, 33)
  test("Marigold") do
    assert_equal("\#%02X%02X%02XFF" % [234, 162, 33],
                 Cairo::Color::MARIGOLD.to_s)
  end

  # Maroon (Crayola): #C32148: (195, 33, 72)
  test("Maroon (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [195, 33, 72],
                 Cairo::Color::MAROON_CRAYOLA.to_s)
  end

  # Maroon (HTML/CSS): #800000: (128, 0, 0)
  test("Maroon (HTML/CSS)") do
    assert_equal("\#%02X%02X%02XFF" % [128, 0, 0],
                 Cairo::Color::MAROON_HTML_CSS.to_s)
  end

  # Maroon (X11): #B03060: (176, 48, 96)
  test("Maroon (X11)") do
    assert_equal("\#%02X%02X%02XFF" % [176, 48, 96],
                 Cairo::Color::MAROON_X11.to_s)
  end

  # Mauve: #E0B0FF: (224, 176, 255)
  test("Mauve") do
    assert_equal("\#%02X%02X%02XFF" % [224, 176, 255],
                 Cairo::Color::MAUVE.to_s)
  end

  # Mauve taupe: #915F6D: (145, 95, 109)
  test("Mauve taupe") do
    assert_equal("\#%02X%02X%02XFF" % [145, 95, 109],
                 Cairo::Color::MAUVE_TAUPE.to_s)
  end

  # Mauvelous: #EF98AA: (239, 152, 170)
  test("Mauvelous") do
    assert_equal("\#%02X%02X%02XFF" % [239, 152, 170],
                 Cairo::Color::MAUVELOUS.to_s)
  end

  # Maximum Blue: #47ABCC: (71, 171, 204)
  test("Maximum Blue") do
    assert_equal("\#%02X%02X%02XFF" % [71, 171, 204],
                 Cairo::Color::MAXIMUM_BLUE.to_s)
  end

  # Maximum Blue Green: #30BFBF: (48, 191, 191)
  test("Maximum Blue Green") do
    assert_equal("\#%02X%02X%02XFF" % [48, 191, 191],
                 Cairo::Color::MAXIMUM_BLUE_GREEN.to_s)
  end

  # Maximum Blue Purple: #ACACE6: (172, 172, 230)
  test("Maximum Blue Purple") do
    assert_equal("\#%02X%02X%02XFF" % [172, 172, 230],
                 Cairo::Color::MAXIMUM_BLUE_PURPLE.to_s)
  end

  # Maximum Green: #5E8C31: (94, 140, 49)
  test("Maximum Green") do
    assert_equal("\#%02X%02X%02XFF" % [94, 140, 49],
                 Cairo::Color::MAXIMUM_GREEN.to_s)
  end

  # Maximum Green Yellow: #D9E650: (217, 230, 80)
  test("Maximum Green Yellow") do
    assert_equal("\#%02X%02X%02XFF" % [217, 230, 80],
                 Cairo::Color::MAXIMUM_GREEN_YELLOW.to_s)
  end

  # Maximum orange: #FF5B00: (255, 91, 0)
  test("Maximum orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 91, 0],
                 Cairo::Color::MAXIMUM_ORANGE.to_s)
  end

  # Maximum Purple: #733380: (115, 51, 128)
  test("Maximum Purple") do
    assert_equal("\#%02X%02X%02XFF" % [115, 51, 128],
                 Cairo::Color::MAXIMUM_PURPLE.to_s)
  end

  # Maximum pink: #F6A5F2: (246, 165, 242)
  test("Maximum pink") do
    assert_equal("\#%02X%02X%02XFF" % [246, 165, 242],
                 Cairo::Color::MAXIMUM_PINK.to_s)
  end

  # Maximum red: #D92121: (217, 33, 33)
  test("Maximum red") do
    assert_equal("\#%02X%02X%02XFF" % [217, 33, 33],
                 Cairo::Color::MAXIMUM_RED.to_s)
  end

  # Maximum Red Purple: #A63A79: (166, 58, 121)
  test("Maximum Red Purple") do
    assert_equal("\#%02X%02X%02XFF" % [166, 58, 121],
                 Cairo::Color::MAXIMUM_RED_PURPLE.to_s)
  end

  # Maximum violet: #892F77: (137, 47, 119)
  test("Maximum violet") do
    assert_equal("\#%02X%02X%02XFF" % [137, 47, 119],
                 Cairo::Color::MAXIMUM_VIOLET.to_s)
  end

  # Maximum yellow: #FAFA37: (250, 250, 55)
  test("Maximum yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 250, 55],
                 Cairo::Color::MAXIMUM_YELLOW.to_s)
  end

  # Maximum yellow red: #F2BA49: (242, 186, 73)
  test("Maximum yellow red") do
    assert_equal("\#%02X%02X%02XFF" % [242, 186, 73],
                 Cairo::Color::MAXIMUM_YELLOW_RED.to_s)
  end

  # May green: #4C9141: (76, 145, 65)
  test("May green") do
    assert_equal("\#%02X%02X%02XFF" % [76, 145, 65],
                 Cairo::Color::MAY_GREEN.to_s)
  end

  # Maya blue: #73C2FB: (115, 194, 251)
  test("Maya blue") do
    assert_equal("\#%02X%02X%02XFF" % [115, 194, 251],
                 Cairo::Color::MAYA_BLUE.to_s)
  end

  # Meat brown: #E5B73B: (229, 183, 59)
  test("Meat brown") do
    assert_equal("\#%02X%02X%02XFF" % [229, 183, 59],
                 Cairo::Color::MEAT_BROWN.to_s)
  end

  # Medium aquamarine: #66DDAA: (102, 221, 170)
  test("Medium aquamarine") do
    assert_equal("\#%02X%02X%02XFF" % [102, 221, 170],
                 Cairo::Color::MEDIUM_AQUAMARINE.to_s)
  end

  # Medium blue: #0000CD: (0, 0, 205)
  test("Medium blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 205],
                 Cairo::Color::MEDIUM_BLUE.to_s)
  end

  # Medium candy apple red: #E2062C: (226, 6, 44)
  test("Medium candy apple red") do
    assert_equal("\#%02X%02X%02XFF" % [226, 6, 44],
                 Cairo::Color::MEDIUM_CANDY_APPLE_RED.to_s)
  end

  # Medium carmine: #AF4035: (175, 64, 53)
  test("Medium carmine") do
    assert_equal("\#%02X%02X%02XFF" % [175, 64, 53],
                 Cairo::Color::MEDIUM_CARMINE.to_s)
  end

  # Medium champagne: #F3E5AB: (243, 229, 171)
  test("Medium champagne") do
    assert_equal("\#%02X%02X%02XFF" % [243, 229, 171],
                 Cairo::Color::MEDIUM_CHAMPAGNE.to_s)
  end

  # Medium electric blue: #035096: (3, 80, 150)
  test("Medium electric blue") do
    assert_equal("\#%02X%02X%02XFF" % [3, 80, 150],
                 Cairo::Color::MEDIUM_ELECTRIC_BLUE.to_s)
  end

  # Medium green: #037949: (3, 121, 73)
  test("Medium green") do
    assert_equal("\#%02X%02X%02XFF" % [3, 121, 73],
                 Cairo::Color::MEDIUM_GREEN.to_s)
  end

  # Medium jungle green: #1C352D: (28, 53, 45)
  test("Medium jungle green") do
    assert_equal("\#%02X%02X%02XFF" % [28, 53, 45],
                 Cairo::Color::MEDIUM_JUNGLE_GREEN.to_s)
  end

  # Medium lavender magenta: #DDA0DD: (221, 160, 221)
  test("Medium lavender magenta") do
    assert_equal("\#%02X%02X%02XFF" % [221, 160, 221],
                 Cairo::Color::MEDIUM_LAVENDER_MAGENTA.to_s)
  end

  # Medium orange: #FF7802: (255, 120, 2)
  test("Medium orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 120, 2],
                 Cairo::Color::MEDIUM_ORANGE.to_s)
  end

  # Medium orchid: #BA55D3: (186, 85, 211)
  test("Medium orchid") do
    assert_equal("\#%02X%02X%02XFF" % [186, 85, 211],
                 Cairo::Color::MEDIUM_ORCHID.to_s)
  end

  # Medium Persian blue: #0067A5: (0, 103, 165)
  test("Medium Persian blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 103, 165],
                 Cairo::Color::MEDIUM_PERSIAN_BLUE.to_s)
  end

  # Medium pink: #FE6E9F: (254, 110, 159)
  test("Medium pink") do
    assert_equal("\#%02X%02X%02XFF" % [254, 110, 159],
                 Cairo::Color::MEDIUM_PINK.to_s)
  end

  # Medium purple: #9370DB: (147, 112, 219)
  test("Medium purple") do
    assert_equal("\#%02X%02X%02XFF" % [147, 112, 219],
                 Cairo::Color::MEDIUM_PURPLE.to_s)
  end

  # Medium red: #B10304: (177, 3, 4)
  test("Medium red") do
    assert_equal("\#%02X%02X%02XFF" % [177, 3, 4],
                 Cairo::Color::MEDIUM_RED.to_s)
  end

  # Medium red-violet: #BB3385: (187, 51, 133)
  test("Medium red-violet") do
    assert_equal("\#%02X%02X%02XFF" % [187, 51, 133],
                 Cairo::Color::MEDIUM_RED_VIOLET.to_s)
  end

  # Medium ruby: #AA4069: (170, 64, 105)
  test("Medium ruby") do
    assert_equal("\#%02X%02X%02XFF" % [170, 64, 105],
                 Cairo::Color::MEDIUM_RUBY.to_s)
  end

  # Medium sea green: #3CB371: (60, 179, 113)
  test("Medium sea green") do
    assert_equal("\#%02X%02X%02XFF" % [60, 179, 113],
                 Cairo::Color::MEDIUM_SEA_GREEN.to_s)
  end

  # Medium sky blue: #80DAEB: (128, 218, 235)
  test("Medium sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [128, 218, 235],
                 Cairo::Color::MEDIUM_SKY_BLUE.to_s)
  end

  # Medium slate blue: #7B68EE: (123, 104, 238)
  test("Medium slate blue") do
    assert_equal("\#%02X%02X%02XFF" % [123, 104, 238],
                 Cairo::Color::MEDIUM_SLATE_BLUE.to_s)
  end

  # Medium spring bud: #C9DC87: (201, 220, 135)
  test("Medium spring bud") do
    assert_equal("\#%02X%02X%02XFF" % [201, 220, 135],
                 Cairo::Color::MEDIUM_SPRING_BUD.to_s)
  end

  # Medium spring green: #00FA9A: (0, 250, 154)
  test("Medium spring green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 250, 154],
                 Cairo::Color::MEDIUM_SPRING_GREEN.to_s)
  end

  # Medium taupe: #674C47: (103, 76, 71)
  test("Medium taupe") do
    assert_equal("\#%02X%02X%02XFF" % [103, 76, 71],
                 Cairo::Color::MEDIUM_TAUPE.to_s)
  end

  # Medium turquoise: #48D1CC: (72, 209, 204)
  test("Medium turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [72, 209, 204],
                 Cairo::Color::MEDIUM_TURQUOISE.to_s)
  end

  # Medium Tuscan red: #79443B: (121, 68, 59)
  test("Medium Tuscan red") do
    assert_equal("\#%02X%02X%02XFF" % [121, 68, 59],
                 Cairo::Color::MEDIUM_TUSCAN_RED.to_s)
  end

  # Medium vermilion: #D9603B: (217, 96, 59)
  test("Medium vermilion") do
    assert_equal("\#%02X%02X%02XFF" % [217, 96, 59],
                 Cairo::Color::MEDIUM_VERMILION.to_s)
  end

  # Medium violet: #65315F: (101, 49, 95)
  test("Medium violet") do
    assert_equal("\#%02X%02X%02XFF" % [101, 49, 95],
                 Cairo::Color::MEDIUM_VIOLET.to_s)
  end

  # Medium violet-red: #C71585: (199, 21, 133)
  test("Medium violet-red") do
    assert_equal("\#%02X%02X%02XFF" % [199, 21, 133],
                 Cairo::Color::MEDIUM_VIOLET_RED.to_s)
  end

  # Medium yellow: #FFE302: (255, 227, 2)
  test("Medium yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 227, 2],
                 Cairo::Color::MEDIUM_YELLOW.to_s)
  end

  # Mellow apricot: #F8B878: (248, 184, 120)
  test("Mellow apricot") do
    assert_equal("\#%02X%02X%02XFF" % [248, 184, 120],
                 Cairo::Color::MELLOW_APRICOT.to_s)
  end

  # Mellow yellow: #F8DE7E: (248, 222, 126)
  test("Mellow yellow") do
    assert_equal("\#%02X%02X%02XFF" % [248, 222, 126],
                 Cairo::Color::MELLOW_YELLOW.to_s)
  end

  # Melon: #FDBCB4: (253, 188, 180)
  test("Melon") do
    assert_equal("\#%02X%02X%02XFF" % [253, 188, 180],
                 Cairo::Color::MELON.to_s)
  end

  # Melon (Crayola): #FEBAAD: (254, 186, 173)
  test("Melon (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [254, 186, 173],
                 Cairo::Color::MELON_CRAYOLA.to_s)
  end

  # Menthol: #C1F9A2: (193, 249, 162)
  test("Menthol") do
    assert_equal("\#%02X%02X%02XFF" % [193, 249, 162],
                 Cairo::Color::MENTHOL.to_s)
  end

  # Metallic blue: #32527B: (50, 82, 123)
  test("Metallic blue") do
    assert_equal("\#%02X%02X%02XFF" % [50, 82, 123],
                 Cairo::Color::METALLIC_BLUE.to_s)
  end

  # Metallic bronze: #A97142: (169, 113, 66)
  test("Metallic bronze") do
    assert_equal("\#%02X%02X%02XFF" % [169, 113, 66],
                 Cairo::Color::METALLIC_BRONZE.to_s)
  end

  # Metallic brown: #AC4313: (172, 67, 19)
  test("Metallic brown") do
    assert_equal("\#%02X%02X%02XFF" % [172, 67, 19],
                 Cairo::Color::METALLIC_BROWN.to_s)
  end

  # Metallic gold: #D3AF37: (211, 175, 55)
  test("Metallic gold") do
    assert_equal("\#%02X%02X%02XFF" % [211, 175, 55],
                 Cairo::Color::METALLIC_GOLD.to_s)
  end

  # Metallic green: #296E01: (41, 110, 1)
  test("Metallic green") do
    assert_equal("\#%02X%02X%02XFF" % [41, 110, 1],
                 Cairo::Color::METALLIC_GREEN.to_s)
  end

  # Metallic orange: #DA680F: (218, 104, 15)
  test("Metallic orange") do
    assert_equal("\#%02X%02X%02XFF" % [218, 104, 15],
                 Cairo::Color::METALLIC_ORANGE.to_s)
  end

  # Metallic pink: #EDA6C4: (237, 166, 196)
  test("Metallic pink") do
    assert_equal("\#%02X%02X%02XFF" % [237, 166, 196],
                 Cairo::Color::METALLIC_PINK.to_s)
  end

  # Metallic red: #A62C2B: (166, 44, 43)
  test("Metallic red") do
    assert_equal("\#%02X%02X%02XFF" % [166, 44, 43],
                 Cairo::Color::METALLIC_RED.to_s)
  end

  # Metallic Seaweed: #0A7E8C: (10, 126, 140)
  test("Metallic Seaweed") do
    assert_equal("\#%02X%02X%02XFF" % [10, 126, 140],
                 Cairo::Color::METALLIC_SEAWEED.to_s)
  end

  # Metallic silver: #A8A9AD: (168, 169, 173)
  test("Metallic silver") do
    assert_equal("\#%02X%02X%02XFF" % [168, 169, 173],
                 Cairo::Color::METALLIC_SILVER.to_s)
  end

  # Metallic Sunburst: #9C7C38: (156, 124, 56)
  test("Metallic Sunburst") do
    assert_equal("\#%02X%02X%02XFF" % [156, 124, 56],
                 Cairo::Color::METALLIC_SUNBURST.to_s)
  end

  # Metallic violet: #5B0A91: (90, 10, 145)
  test("Metallic violet") do
    assert_equal("\#%02X%02X%02XFF" % [90, 10, 145],
                 Cairo::Color::METALLIC_VIOLET.to_s)
  end

  # Metallic yellow: #FDCC0D: (253, 204, 13)
  test("Metallic yellow") do
    assert_equal("\#%02X%02X%02XFF" % [253, 204, 13],
                 Cairo::Color::METALLIC_YELLOW.to_s)
  end

  # Mexican pink: #E4007C: (228, 0, 124)
  test("Mexican pink") do
    assert_equal("\#%02X%02X%02XFF" % [228, 0, 124],
                 Cairo::Color::MEXICAN_PINK.to_s)
  end

  # Microsoft blue: #00A2ED: (0, 162, 237)
  test("Microsoft blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 162, 237],
                 Cairo::Color::MICROSOFT_BLUE.to_s)
  end

  # Microsoft Edge blue: #0078D7: (0, 120, 215)
  test("Microsoft Edge blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 120, 215],
                 Cairo::Color::MICROSOFT_EDGE_BLUE.to_s)
  end

  # Microsoft green: #7DB700: (125, 183, 0)
  test("Microsoft green") do
    assert_equal("\#%02X%02X%02XFF" % [125, 183, 0],
                 Cairo::Color::MICROSOFT_GREEN.to_s)
  end

  # Microsoft red: #F04E1F: (240, 78, 31)
  test("Microsoft red") do
    assert_equal("\#%02X%02X%02XFF" % [240, 78, 31],
                 Cairo::Color::MICROSOFT_RED.to_s)
  end

  # Microsoft yellow: #FDB900: (253, 185, 0)
  test("Microsoft yellow") do
    assert_equal("\#%02X%02X%02XFF" % [253, 185, 0],
                 Cairo::Color::MICROSOFT_YELLOW.to_s)
  end

  # Middle blue: #7ED4E6: (126, 212, 230)
  test("Middle blue") do
    assert_equal("\#%02X%02X%02XFF" % [126, 212, 230],
                 Cairo::Color::MIDDLE_BLUE.to_s)
  end

  # Middle blue green: #8DD9CC: (141, 217, 204)
  test("Middle blue green") do
    assert_equal("\#%02X%02X%02XFF" % [141, 217, 204],
                 Cairo::Color::MIDDLE_BLUE_GREEN.to_s)
  end

  # Middle blue purple: #8B72BE: (139, 114, 190)
  test("Middle blue purple") do
    assert_equal("\#%02X%02X%02XFF" % [139, 114, 190],
                 Cairo::Color::MIDDLE_BLUE_PURPLE.to_s)
  end

  # Middle grey: #8B8680: (139, 134, 128)
  test("Middle grey") do
    assert_equal("\#%02X%02X%02XFF" % [139, 134, 128],
                 Cairo::Color::MIDDLE_GREY.to_s)
  end

  # Middle green: #4D8C57: (77, 140, 87)
  test("Middle green") do
    assert_equal("\#%02X%02X%02XFF" % [77, 140, 87],
                 Cairo::Color::MIDDLE_GREEN.to_s)
  end

  # Middle green yellow: #ACBF60: (172, 191, 96)
  test("Middle green yellow") do
    assert_equal("\#%02X%02X%02XFF" % [172, 191, 96],
                 Cairo::Color::MIDDLE_GREEN_YELLOW.to_s)
  end

  # Middle purple: #D982B5: (217, 130, 181)
  test("Middle purple") do
    assert_equal("\#%02X%02X%02XFF" % [217, 130, 181],
                 Cairo::Color::MIDDLE_PURPLE.to_s)
  end

  # Middle red: #E58E73: (229, 144, 115)
  test("Middle red") do
    assert_equal("\#%02X%02X%02XFF" % [229, 144, 115],
                 Cairo::Color::MIDDLE_RED.to_s)
  end

  # Middle red purple: #A55353: (165, 83, 83)
  test("Middle red purple") do
    assert_equal("\#%02X%02X%02XFF" % [165, 83, 83],
                 Cairo::Color::MIDDLE_RED_PURPLE.to_s)
  end

  # Middle yellow: #FFEB00: (255, 235, 0)
  test("Middle yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 235, 0],
                 Cairo::Color::MIDDLE_YELLOW.to_s)
  end

  # Middle yellow red: #ECB176: (236, 177, 118)
  test("Middle yellow red") do
    assert_equal("\#%02X%02X%02XFF" % [236, 177, 118],
                 Cairo::Color::MIDDLE_YELLOW_RED.to_s)
  end

  # Midnight: #702670: (112, 38, 112)
  test("Midnight") do
    assert_equal("\#%02X%02X%02XFF" % [112, 38, 112],
                 Cairo::Color::MIDNIGHT.to_s)
  end

  # Midnight blue: #191970: (25, 25, 112)
  test("Midnight blue") do
    assert_equal("\#%02X%02X%02XFF" % [25, 25, 112],
                 Cairo::Color::MIDNIGHT_BLUE.to_s)
  end

  # Midnight green (eagle green): #004953: (0, 73, 83)
  test("Midnight green (eagle green)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 73, 83],
                 Cairo::Color::MIDNIGHT_GREEN_EAGLE_GREEN.to_s)
  end

  # Mikado yellow: #FFC40C: (255, 196, 12)
  test("Mikado yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 196, 12],
                 Cairo::Color::MIKADO_YELLOW.to_s)
  end

  # Milk: #FDFFF5: (253, 255, 245)
  test("Milk") do
    assert_equal("\#%02X%02X%02XFF" % [253, 255, 245],
                 Cairo::Color::MILK.to_s)
  end

  # Milk chocolate: #84563C: (132, 86, 60)
  test("Milk chocolate") do
    assert_equal("\#%02X%02X%02XFF" % [132, 86, 60],
                 Cairo::Color::MILK_CHOCOLATE.to_s)
  end

  # Mimi pink: #FFDAE9: (255, 218, 233)
  test("Mimi pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 218, 233],
                 Cairo::Color::MIMI_PINK.to_s)
  end

  # Mindaro: #E3F988: (227, 249, 136)
  test("Mindaro") do
    assert_equal("\#%02X%02X%02XFF" % [227, 249, 136],
                 Cairo::Color::MINDARO.to_s)
  end

  # Ming: #36747D: (54, 116, 125)
  test("Ming") do
    assert_equal("\#%02X%02X%02XFF" % [54, 116, 125],
                 Cairo::Color::MING.to_s)
  end

  # Minion yellow: #F5E050: (245, 220, 80)
  test("Minion yellow") do
    assert_equal("\#%02X%02X%02XFF" % [245, 220, 80],
                 Cairo::Color::MINION_YELLOW.to_s)
  end

  # Mint: #3EB489: (62, 180, 137)
  test("Mint") do
    assert_equal("\#%02X%02X%02XFF" % [62, 180, 137],
                 Cairo::Color::MINT.to_s)
  end

  # Mint cream: #F5FFFA: (245, 255, 250)
  test("Mint cream") do
    assert_equal("\#%02X%02X%02XFF" % [245, 255, 250],
                 Cairo::Color::MINT_CREAM.to_s)
  end

  # Mint green: #98FF98: (152, 255, 152)
  test("Mint green") do
    assert_equal("\#%02X%02X%02XFF" % [152, 255, 152],
                 Cairo::Color::MINT_GREEN.to_s)
  end

  # Misty Moss: #BBB477: (187, 180, 119)
  test("Misty Moss") do
    assert_equal("\#%02X%02X%02XFF" % [187, 180, 119],
                 Cairo::Color::MISTY_MOSS.to_s)
  end

  # Misty rose: #FFE4E1: (255, 228, 225)
  test("Misty rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 228, 225],
                 Cairo::Color::MISTY_ROSE.to_s)
  end

  # Moccasin: #FAEBD7: (250, 235, 215)
  test("Moccasin") do
    assert_equal("\#%02X%02X%02XFF" % [250, 235, 215],
                 Cairo::Color::MOCCASIN.to_s)
  end

  # Mocha: #BEA493: (190, 164, 147)
  test("Mocha") do
    assert_equal("\#%02X%02X%02XFF" % [190, 164, 147],
                 Cairo::Color::MOCHA.to_s)
  end

  # Mode beige: #967117: (150, 113, 23)
  test("Mode beige") do
    assert_equal("\#%02X%02X%02XFF" % [150, 113, 23],
                 Cairo::Color::MODE_BEIGE.to_s)
  end

  # Moonstone: #3AA8C1: (58, 168, 193)
  test("Moonstone") do
    assert_equal("\#%02X%02X%02XFF" % [58, 168, 193],
                 Cairo::Color::MOONSTONE.to_s)
  end

  # Moonstone blue: #73A9C2: (115, 169, 194)
  test("Moonstone blue") do
    assert_equal("\#%02X%02X%02XFF" % [115, 169, 194],
                 Cairo::Color::MOONSTONE_BLUE.to_s)
  end

  # Mordant red 19: #AE0C00: (174, 12, 0)
  test("Mordant red 19") do
    assert_equal("\#%02X%02X%02XFF" % [174, 12, 0],
                 Cairo::Color::MORDANT_RED_19.to_s)
  end

  # Morning blue: #8DA399: (141, 163, 153)
  test("Morning blue") do
    assert_equal("\#%02X%02X%02XFF" % [141, 163, 153],
                 Cairo::Color::MORNING_BLUE.to_s)
  end

  # Moss green: #8A9A5B: (138, 154, 91)
  test("Moss green") do
    assert_equal("\#%02X%02X%02XFF" % [138, 154, 91],
                 Cairo::Color::MOSS_GREEN.to_s)
  end

  # Mountain Meadow: #30BA8F: (48, 186, 143)
  test("Mountain Meadow") do
    assert_equal("\#%02X%02X%02XFF" % [48, 186, 143],
                 Cairo::Color::MOUNTAIN_MEADOW.to_s)
  end

  # Mountbatten pink: #997A8D: (153, 122, 141)
  test("Mountbatten pink") do
    assert_equal("\#%02X%02X%02XFF" % [153, 122, 141],
                 Cairo::Color::MOUNTBATTEN_PINK.to_s)
  end

  # MSU green: #18453B: (24, 69, 59)
  test("MSU green") do
    assert_equal("\#%02X%02X%02XFF" % [24, 69, 59],
                 Cairo::Color::MSU_GREEN.to_s)
  end

  # Mud: #70543E: (111, 83, 61)
  test("Mud") do
    assert_equal("\#%02X%02X%02XFF" % [111, 83, 61],
                 Cairo::Color::MUD.to_s)
  end

  # Mughal green: #306030: (48, 96, 48)
  test("Mughal green") do
    assert_equal("\#%02X%02X%02XFF" % [48, 96, 48],
                 Cairo::Color::MUGHAL_GREEN.to_s)
  end

  # Mulberry: #C54B8C: (197, 75, 140)
  test("Mulberry") do
    assert_equal("\#%02X%02X%02XFF" % [197, 75, 140],
                 Cairo::Color::MULBERRY.to_s)
  end

  # Mulberry (Crayola): #C8509B: (200, 80, 155)
  test("Mulberry (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [200, 80, 155],
                 Cairo::Color::MULBERRY_CRAYOLA.to_s)
  end

  # Mummy's Tomb: #828E84: (130, 142, 132)
  test("Mummy's Tomb") do
    assert_equal("\#%02X%02X%02XFF" % [130, 142, 132],
                 Cairo::Color::MUMMYS_TOMB.to_s)
  end

  # Mustard: #FFDB58: (255, 219, 88)
  test("Mustard") do
    assert_equal("\#%02X%02X%02XFF" % [255, 219, 88],
                 Cairo::Color::MUSTARD.to_s)
  end

  # Mustard brown: #CD7A00: (205, 122, 0)
  test("Mustard brown") do
    assert_equal("\#%02X%02X%02XFF" % [205, 122, 0],
                 Cairo::Color::MUSTARD_BROWN.to_s)
  end

  # Mustard green: #6E6E30: (110, 110, 48)
  test("Mustard green") do
    assert_equal("\#%02X%02X%02XFF" % [110, 110, 48],
                 Cairo::Color::MUSTARD_GREEN.to_s)
  end

  # Mustard yellow: #E1AD01: (255, 173, 1)
  test("Mustard yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 173, 1],
                 Cairo::Color::MUSTARD_YELLOW.to_s)
  end

  # Myrtle green: #317873: (49, 120, 115)
  test("Myrtle green") do
    assert_equal("\#%02X%02X%02XFF" % [49, 120, 115],
                 Cairo::Color::MYRTLE_GREEN.to_s)
  end

  # Mystic: #D65282: (214, 82, 130)
  test("Mystic") do
    assert_equal("\#%02X%02X%02XFF" % [214, 82, 130],
                 Cairo::Color::MYSTIC.to_s)
  end

  # Mystic maroon: #AD4379: (173, 67, 121)
  test("Mystic maroon") do
    assert_equal("\#%02X%02X%02XFF" % [173, 67, 121],
                 Cairo::Color::MYSTIC_MAROON.to_s)
  end

  # Mystic red: #FF5500: (255, 34, 0)
  test("Mystic red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 34, 0],
                 Cairo::Color::MYSTIC_RED.to_s)
  end

  # Nadeshiko pink: #F6ADC6: (246, 173, 198)
  test("Nadeshiko pink") do
    assert_equal("\#%02X%02X%02XFF" % [246, 173, 198],
                 Cairo::Color::NADESHIKO_PINK.to_s)
  end

  # Napier green: #2A8000: (42, 128, 0)
  test("Napier green") do
    assert_equal("\#%02X%02X%02XFF" % [42, 128, 0],
                 Cairo::Color::NAPIER_GREEN.to_s)
  end

  # Naples yellow: #FADA5E: (250, 218, 94)
  test("Naples yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 218, 94],
                 Cairo::Color::NAPLES_YELLOW.to_s)
  end

  # Navajo white: #FFDEAD: (255, 222, 173)
  test("Navajo white") do
    assert_equal("\#%02X%02X%02XFF" % [255, 222, 173],
                 Cairo::Color::NAVAJO_WHITE.to_s)
  end

  # Navy blue: #000080: (0, 0, 128)
  test("Navy blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 128],
                 Cairo::Color::NAVY_BLUE.to_s)
  end

  # Navy blue (Crayola): #1974D2: (25, 116, 210)
  test("Navy blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [25, 116, 210],
                 Cairo::Color::NAVY_BLUE_CRAYOLA.to_s)
  end

  # Navy purple: #9457EB: (148, 87, 235)
  test("Navy purple") do
    assert_equal("\#%02X%02X%02XFF" % [148, 87, 235],
                 Cairo::Color::NAVY_PURPLE.to_s)
  end

  # Neon blue: #1B03A3: (27, 3, 163)
  test("Neon blue") do
    assert_equal("\#%02X%02X%02XFF" % [27, 3, 163],
                 Cairo::Color::NEON_BLUE.to_s)
  end

  # Neon brown: #C3732A: (195, 115, 42)
  test("Neon brown") do
    assert_equal("\#%02X%02X%02XFF" % [195, 115, 42],
                 Cairo::Color::NEON_BROWN.to_s)
  end

  # Neon Carrot: #FFA343: (255, 163, 67)
  test("Neon Carrot") do
    assert_equal("\#%02X%02X%02XFF" % [255, 163, 67],
                 Cairo::Color::NEON_CARROT.to_s)
  end

  # Neon cyan: #00FEFC: (0, 254, 252)
  test("Neon cyan") do
    assert_equal("\#%02X%02X%02XFF" % [0, 254, 252],
                 Cairo::Color::NEON_CYAN.to_s)
  end

  # Neon fuchsia: #FE4164: (254, 65, 100)
  test("Neon fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [254, 65, 100],
                 Cairo::Color::NEON_FUCHSIA.to_s)
  end

  # Neon gold: #CFAA01: (207, 170, 1)
  test("Neon gold") do
    assert_equal("\#%02X%02X%02XFF" % [207, 170, 1],
                 Cairo::Color::NEON_GOLD.to_s)
  end

  # Neon gray: #808080: (128, 128, 128)
  test("Neon gray") do
    assert_equal("\#%02X%02X%02XFF" % [128, 128, 128],
                 Cairo::Color::NEON_GRAY.to_s)
  end

  # Neon dark green: #008443: (0, 132, 67)
  test("Neon dark green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 132, 67],
                 Cairo::Color::NEON_DARK_GREEN.to_s)
  end

  # Neon green: #139B42: (19, 155, 66)
  test("Neon green") do
    assert_equal("\#%02X%02X%02XFF" % [19, 155, 66],
                 Cairo::Color::NEON_GREEN.to_s)
  end

  # Neon pink: #FE347E: (254, 52, 126)
  test("Neon pink") do
    assert_equal("\#%02X%02X%02XFF" % [254, 52, 126],
                 Cairo::Color::NEON_PINK.to_s)
  end

  # Neon purple: #9457EB: (148, 87, 235)
  test("Neon purple") do
    assert_equal("\#%02X%02X%02XFF" % [148, 87, 235],
                 Cairo::Color::NEON_PURPLE.to_s)
  end

  # Neon red: #FF1818: (255, 24, 24)
  test("Neon red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 24, 24],
                 Cairo::Color::NEON_RED.to_s)
  end

  # Neon scarlet: #FF2603: (255, 38, 3)
  test("Neon scarlet") do
    assert_equal("\#%02X%02X%02XFF" % [255, 38, 3],
                 Cairo::Color::NEON_SCARLET.to_s)
  end

  # Neon silver: #CCCCCC: (204, 204, 204)
  test("Neon silver") do
    assert_equal("\#%02X%02X%02XFF" % [204, 204, 204],
                 Cairo::Color::NEON_SILVER.to_s)
  end

  # Neon tangerine: #F6890A: (246, 137, 10)
  test("Neon tangerine") do
    assert_equal("\#%02X%02X%02XFF" % [246, 137, 10],
                 Cairo::Color::NEON_TANGERINE.to_s)
  end

  # Neon yellow: #FFF700: (255, 247, 0)
  test("Neon yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 247, 0],
                 Cairo::Color::NEON_YELLOW.to_s)
  end

  # New Car: #214FC6: (33, 79, 198)
  test("New Car") do
    assert_equal("\#%02X%02X%02XFF" % [33, 79, 198],
                 Cairo::Color::NEW_CAR.to_s)
  end

  # New York pink: #D7837F: (215, 131, 127)
  test("New York pink") do
    assert_equal("\#%02X%02X%02XFF" % [215, 131, 127],
                 Cairo::Color::NEW_YORK_PINK.to_s)
  end

  # Nickel: #727472: (114, 116, 114)
  test("Nickel") do
    assert_equal("\#%02X%02X%02XFF" % [114, 116, 114],
                 Cairo::Color::NICKEL.to_s)
  end

  # Nintendo red: #E4000F: (228, 0, 15)
  test("Nintendo red") do
    assert_equal("\#%02X%02X%02XFF" % [228, 0, 15],
                 Cairo::Color::NINTENDO_RED.to_s)
  end

  # Non-photo blue: #A4DDED: (164, 221, 237)
  test("Non-photo blue") do
    assert_equal("\#%02X%02X%02XFF" % [164, 221, 237],
                 Cairo::Color::NON_PHOTO_BLUE.to_s)
  end

  # Nyanza: #E9FFDB: (233, 255, 219)
  test("Nyanza") do
    assert_equal("\#%02X%02X%02XFF" % [233, 255, 219],
                 Cairo::Color::NYANZA.to_s)
  end

  # Ocean blue: #4F42B5: (79, 66, 181)
  test("Ocean blue") do
    assert_equal("\#%02X%02X%02XFF" % [79, 66, 181],
                 Cairo::Color::OCEAN_BLUE.to_s)
  end

  # Ocean boat blue: #0077BE: (0, 119, 190)
  test("Ocean boat blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 119, 190],
                 Cairo::Color::OCEAN_BOAT_BLUE.to_s)
  end

  # Ocean green: #48BF91: (72, 191, 145)
  test("Ocean green") do
    assert_equal("\#%02X%02X%02XFF" % [72, 191, 145],
                 Cairo::Color::OCEAN_GREEN.to_s)
  end

  # Ochre: #CC7722: (204, 119, 34)
  test("Ochre") do
    assert_equal("\#%02X%02X%02XFF" % [204, 119, 34],
                 Cairo::Color::OCHRE.to_s)
  end

  # Office green: #008000: (0, 128, 0)
  test("Office green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 128, 0],
                 Cairo::Color::OFFICE_GREEN.to_s)
  end

  # Ogre Odor: #FD5240: (253, 82, 64)
  test("Ogre Odor") do
    assert_equal("\#%02X%02X%02XFF" % [253, 82, 64],
                 Cairo::Color::OGRE_ODOR.to_s)
  end

  # Old burgundy: #43302E: (67, 48, 46)
  test("Old burgundy") do
    assert_equal("\#%02X%02X%02XFF" % [67, 48, 46],
                 Cairo::Color::OLD_BURGUNDY.to_s)
  end

  # Old gold: #CFB53B: (207, 181, 59)
  test("Old gold") do
    assert_equal("\#%02X%02X%02XFF" % [207, 181, 59],
                 Cairo::Color::OLD_GOLD.to_s)
  end

  # Old heliotrope: #563C5C: (86, 60, 92)
  test("Old heliotrope") do
    assert_equal("\#%02X%02X%02XFF" % [86, 60, 92],
                 Cairo::Color::OLD_HELIOTROPE.to_s)
  end

  # Old lace: #FDF5E6: (253, 245, 230)
  test("Old lace") do
    assert_equal("\#%02X%02X%02XFF" % [253, 245, 230],
                 Cairo::Color::OLD_LACE.to_s)
  end

  # Old lavender: #796878: (121, 104, 120)
  test("Old lavender") do
    assert_equal("\#%02X%02X%02XFF" % [121, 104, 120],
                 Cairo::Color::OLD_LAVENDER.to_s)
  end

  # Old mauve: #673147: (103, 49, 71)
  test("Old mauve") do
    assert_equal("\#%02X%02X%02XFF" % [103, 49, 71],
                 Cairo::Color::OLD_MAUVE.to_s)
  end

  # Old moss green: #867E36: (134, 126, 54)
  test("Old moss green") do
    assert_equal("\#%02X%02X%02XFF" % [134, 126, 54],
                 Cairo::Color::OLD_MOSS_GREEN.to_s)
  end

  # Old rose: #C08081: (192, 128, 129)
  test("Old rose") do
    assert_equal("\#%02X%02X%02XFF" % [192, 128, 129],
                 Cairo::Color::OLD_ROSE.to_s)
  end

  # Old silver: #848482: (132, 132, 130)
  test("Old silver") do
    assert_equal("\#%02X%02X%02XFF" % [132, 132, 130],
                 Cairo::Color::OLD_SILVER.to_s)
  end

  # Olive: #808000: (128, 128, 0)
  test("Olive") do
    assert_equal("\#%02X%02X%02XFF" % [128, 128, 0],
                 Cairo::Color::OLIVE.to_s)
  end

  # Olive drab (#3): #6B8E23: (107, 142, 35)
  test("Olive drab (#3)") do
    assert_equal("\#%02X%02X%02XFF" % [107, 142, 35],
                 Cairo::Color::OLIVE_DRAB3.to_s)
  end

  # Olive drab #7: #3C341F: (60, 52, 31)
  test("Olive drab #7") do
    assert_equal("\#%02X%02X%02XFF" % [60, 52, 31],
                 Cairo::Color::OLIVE_DRAB7.to_s)
  end

  # Olive green: #B5B35C: (181, 179, 92)
  test("Olive green") do
    assert_equal("\#%02X%02X%02XFF" % [181, 179, 92],
                 Cairo::Color::OLIVE_GREEN.to_s)
  end

  # Olivine: #9AB973: (154, 185, 115)
  test("Olivine") do
    assert_equal("\#%02X%02X%02XFF" % [154, 185, 115],
                 Cairo::Color::OLIVINE.to_s)
  end

  # Onyx: #353839: (53, 56, 57)
  test("Onyx") do
    assert_equal("\#%02X%02X%02XFF" % [53, 56, 57],
                 Cairo::Color::ONYX.to_s)
  end

  # Opal: #A8C3BC: (168, 195, 188)
  test("Opal") do
    assert_equal("\#%02X%02X%02XFF" % [168, 195, 188],
                 Cairo::Color::OPAL.to_s)
  end

  # Opera mauve: #B784A7: (183, 132, 167)
  test("Opera mauve") do
    assert_equal("\#%02X%02X%02XFF" % [183, 132, 167],
                 Cairo::Color::OPERA_MAUVE.to_s)
  end

  # Orange: #FF6600: (255, 102, 0)
  test("Orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 102, 0],
                 Cairo::Color::ORANGE.to_s)
  end

  # Orange (color wheel): #FF7F00: (255, 127, 0)
  test("Orange (color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 127, 0],
                 Cairo::Color::ORANGE_COLOR_WHEEL.to_s)
  end

  # Orange (Crayola): #FF7538: (255, 117, 56)
  test("Orange (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 117, 56],
                 Cairo::Color::ORANGE_CRAYOLA.to_s)
  end

  # Orange (Pantone): #FF5800: (255, 88, 0)
  test("Orange (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 88, 0],
                 Cairo::Color::ORANGE_PANTONE.to_s)
  end

  # Orange (RYB): #FB9902: (251, 153, 2)
  test("Orange (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [251, 153, 2],
                 Cairo::Color::ORANGE_RYB.to_s)
  end

  # Orange (web): #FFA500: (255, 165, 0)
  test("Orange (web)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 165, 0],
                 Cairo::Color::ORANGE_WEB.to_s)
  end

  # Orange iced tea: #FF6700: (255, 103, 0)
  test("Orange iced tea") do
    assert_equal("\#%02X%02X%02XFF" % [255, 103, 0],
                 Cairo::Color::ORANGE_ICED_TEA.to_s)
  end

  # Orange peel: #FF9F00: (255, 159, 0)
  test("Orange peel") do
    assert_equal("\#%02X%02X%02XFF" % [255, 159, 0],
                 Cairo::Color::ORANGE_PEEL.to_s)
  end

  # Orange-red: #FF681F: (255, 104, 31)
  test("Orange-red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 104, 31],
                 Cairo::Color::ORANGE_RED.to_s)
  end

  # Orange-red (Crayola): #FF5349: (255, 83, 73)
  test("Orange-red (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 83, 73],
                 Cairo::Color::ORANGE_RED_CRAYOLA.to_s)
  end

  # Orange soda: #E74E14: (231, 78, 20)
  test("Orange soda") do
    assert_equal("\#%02X%02X%02XFF" % [231, 78, 20],
                 Cairo::Color::ORANGE_SODA.to_s)
  end

  # Orange-yellow: #F5BD1F: (245, 189, 31)
  test("Orange-yellow") do
    assert_equal("\#%02X%02X%02XFF" % [245, 189, 31],
                 Cairo::Color::ORANGE_YELLOW.to_s)
  end

  # Orange-yellow (Crayola): #F8D568: (248, 213, 104)
  test("Orange-yellow (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [248, 213, 104],
                 Cairo::Color::ORANGE_YELLOW_CRAYOLA.to_s)
  end

  # Orchid: #DA70D6: (218, 112, 214)
  test("Orchid") do
    assert_equal("\#%02X%02X%02XFF" % [218, 112, 214],
                 Cairo::Color::ORCHID.to_s)
  end

  # Orchid pink: #F2BDCD: (242, 189, 205)
  test("Orchid pink") do
    assert_equal("\#%02X%02X%02XFF" % [242, 189, 205],
                 Cairo::Color::ORCHID_PINK.to_s)
  end

  # Orchid (Crayola): #E29CD2: (226, 156, 210)
  test("Orchid (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [226, 156, 210],
                 Cairo::Color::ORCHID_CRAYOLA.to_s)
  end

  # Orioles orange: #FB4F14: (251, 79, 20)
  test("Orioles orange") do
    assert_equal("\#%02X%02X%02XFF" % [251, 79, 20],
                 Cairo::Color::ORIOLES_ORANGE.to_s)
  end

  # Otter brown: #654321: (101, 67, 33)
  test("Otter brown") do
    assert_equal("\#%02X%02X%02XFF" % [101, 67, 33],
                 Cairo::Color::OTTER_BROWN.to_s)
  end

  # Outer Space: #414A4C: (65, 74, 76)
  test("Outer Space") do
    assert_equal("\#%02X%02X%02XFF" % [65, 74, 76],
                 Cairo::Color::OUTER_SPACE.to_s)
  end

  # Outer space (Crayola): #2D383A: (45, 56, 58)
  test("Outer space (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [45, 56, 58],
                 Cairo::Color::OUTER_SPACE_CRAYOLA.to_s)
  end

  # Outrageous Orange: #FF6E4A: (255, 110, 74)
  test("Outrageous Orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 110, 74],
                 Cairo::Color::OUTRAGEOUS_ORANGE.to_s)
  end

  # Oxblood: #800020: (128, 0, 32)
  test("Oxblood") do
    assert_equal("\#%02X%02X%02XFF" % [128, 0, 32],
                 Cairo::Color::OXBLOOD.to_s)
  end

  # Oxford blue: #002147: (0, 33, 71)
  test("Oxford blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 33, 71],
                 Cairo::Color::OXFORD_BLUE.to_s)
  end

  # Oxley: #6D9A79: (109, 154, 121)
  test("Oxley") do
    assert_equal("\#%02X%02X%02XFF" % [109, 154, 121],
                 Cairo::Color::OXLEY.to_s)
  end

  # OU Crimson red: #990000: (153, 0, 0)
  test("OU Crimson red") do
    assert_equal("\#%02X%02X%02XFF" % [153, 0, 0],
                 Cairo::Color::OU_CRIMSON_RED.to_s)
  end

  # Pacific Blue: #1CA9C9: (28, 169, 201)
  test("Pacific Blue") do
    assert_equal("\#%02X%02X%02XFF" % [28, 169, 201],
                 Cairo::Color::PACIFIC_BLUE.to_s)
  end

  # Pakistan green: #006600: (0, 102, 0)
  test("Pakistan green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 102, 0],
                 Cairo::Color::PAKISTAN_GREEN.to_s)
  end

  # Palatinate blue: #273BE2: (39, 59, 226)
  test("Palatinate blue") do
    assert_equal("\#%02X%02X%02XFF" % [39, 59, 226],
                 Cairo::Color::PALATINATE_BLUE.to_s)
  end

  # Palatinate purple: #682860: (104, 40, 96)
  test("Palatinate purple") do
    assert_equal("\#%02X%02X%02XFF" % [104, 40, 96],
                 Cairo::Color::PALATINATE_PURPLE.to_s)
  end

  # Pale aqua: #BCD4E6: (188, 212, 230)
  test("Pale aqua") do
    assert_equal("\#%02X%02X%02XFF" % [188, 212, 230],
                 Cairo::Color::PALE_AQUA.to_s)
  end

  # Pale blue: #AFEEEE: (175, 238, 238)
  test("Pale blue") do
    assert_equal("\#%02X%02X%02XFF" % [175, 238, 238],
                 Cairo::Color::PALE_BLUE.to_s)
  end

  # Pale brown: #987654: (152, 118, 84)
  test("Pale brown") do
    assert_equal("\#%02X%02X%02XFF" % [152, 118, 84],
                 Cairo::Color::PALE_BROWN.to_s)
  end

  # Pale carmine: #AF4035: (175, 64, 53)
  test("Pale carmine") do
    assert_equal("\#%02X%02X%02XFF" % [175, 64, 53],
                 Cairo::Color::PALE_CARMINE.to_s)
  end

  # Pale cerulean: #9BC4E2: (155, 196, 226)
  test("Pale cerulean") do
    assert_equal("\#%02X%02X%02XFF" % [155, 196, 226],
                 Cairo::Color::PALE_CERULEAN.to_s)
  end

  # Pale chestnut: #DDADAF: (221, 173, 175)
  test("Pale chestnut") do
    assert_equal("\#%02X%02X%02XFF" % [221, 173, 175],
                 Cairo::Color::PALE_CHESTNUT.to_s)
  end

  # Pale copper: #DA8A67: (218, 138, 103)
  test("Pale copper") do
    assert_equal("\#%02X%02X%02XFF" % [218, 138, 103],
                 Cairo::Color::PALE_COPPER.to_s)
  end

  # Pale cornflower blue: #ABCDEF: (171, 205, 239)
  test("Pale cornflower blue") do
    assert_equal("\#%02X%02X%02XFF" % [171, 205, 239],
                 Cairo::Color::PALE_CORNFLOWER_BLUE.to_s)
  end

  # Pale cyan: #87D3F8: (135, 211, 248)
  test("Pale cyan") do
    assert_equal("\#%02X%02X%02XFF" % [135, 211, 248],
                 Cairo::Color::PALE_CYAN.to_s)
  end

  # Pale gold: #E6BE8A: (230, 190, 138)
  test("Pale gold") do
    assert_equal("\#%02X%02X%02XFF" % [230, 190, 138],
                 Cairo::Color::PALE_GOLD.to_s)
  end

  # Pale goldenrod: #EEE8AA: (238, 232, 170)
  test("Pale goldenrod") do
    assert_equal("\#%02X%02X%02XFF" % [238, 232, 170],
                 Cairo::Color::PALE_GOLDENROD.to_s)
  end

  # Pale green: #98FB98: (152, 251, 152)
  test("Pale green") do
    assert_equal("\#%02X%02X%02XFF" % [152, 251, 152],
                 Cairo::Color::PALE_GREEN.to_s)
  end

  # Pale lavender: #DCD0FF: (220, 208, 255)
  test("Pale lavender") do
    assert_equal("\#%02X%02X%02XFF" % [220, 208, 255],
                 Cairo::Color::PALE_LAVENDER.to_s)
  end

  # Pale magenta: #F984E5: (249, 132, 229)
  test("Pale magenta") do
    assert_equal("\#%02X%02X%02XFF" % [249, 132, 229],
                 Cairo::Color::PALE_MAGENTA.to_s)
  end

  # Pale magenta-pink: #FF99CC: (255, 153, 204)
  test("Pale magenta-pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 204],
                 Cairo::Color::PALE_MAGENTA_PINK.to_s)
  end

  # Pale pink: #FADADD: (250, 218, 221)
  test("Pale pink") do
    assert_equal("\#%02X%02X%02XFF" % [250, 218, 221],
                 Cairo::Color::PALE_PINK.to_s)
  end

  # Pale plum: #DDA0DD: (221, 160, 221)
  test("Pale plum") do
    assert_equal("\#%02X%02X%02XFF" % [221, 160, 221],
                 Cairo::Color::PALE_PLUM.to_s)
  end

  # Pale red-violet: #DB7093: (219, 112, 147)
  test("Pale red-violet") do
    assert_equal("\#%02X%02X%02XFF" % [219, 112, 147],
                 Cairo::Color::PALE_RED_VIOLET.to_s)
  end

  # Pale robin egg blue: #96DED1: (150, 222, 209)
  test("Pale robin egg blue") do
    assert_equal("\#%02X%02X%02XFF" % [150, 222, 209],
                 Cairo::Color::PALE_ROBIN_EGG_BLUE.to_s)
  end

  # Pale silver: #C9C0BB: (201, 192, 187)
  test("Pale silver") do
    assert_equal("\#%02X%02X%02XFF" % [201, 192, 187],
                 Cairo::Color::PALE_SILVER.to_s)
  end

  # Pale spring bud: #ECEBBD: (236, 235, 189)
  test("Pale spring bud") do
    assert_equal("\#%02X%02X%02XFF" % [236, 235, 189],
                 Cairo::Color::PALE_SPRING_BUD.to_s)
  end

  # Pale taupe: #BC987E: (188, 152, 126)
  test("Pale taupe") do
    assert_equal("\#%02X%02X%02XFF" % [188, 152, 126],
                 Cairo::Color::PALE_TAUPE.to_s)
  end

  # Pale turquoise: #AFEEEE: (175, 238, 238)
  test("Pale turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [175, 238, 238],
                 Cairo::Color::PALE_TURQUOISE.to_s)
  end

  # Pale violet: #CC99FF: (204, 153, 255)
  test("Pale violet") do
    assert_equal("\#%02X%02X%02XFF" % [204, 153, 255],
                 Cairo::Color::PALE_VIOLET.to_s)
  end

  # Pale violet-red: #DB7093: (219, 112, 147)
  test("Pale violet-red") do
    assert_equal("\#%02X%02X%02XFF" % [219, 112, 147],
                 Cairo::Color::PALE_VIOLET_RED.to_s)
  end

  # Palm Leaf: #6F9940: (111, 153, 64)
  test("Palm Leaf") do
    assert_equal("\#%02X%02X%02XFF" % [111, 153, 64],
                 Cairo::Color::PALM_LEAF.to_s)
  end

  # Pansy purple: #78184A: (120, 24, 74)
  test("Pansy purple") do
    assert_equal("\#%02X%02X%02XFF" % [120, 24, 74],
                 Cairo::Color::PANSY_PURPLE.to_s)
  end

  # Paolo Veronese green: #009B7D: (0, 155, 125)
  test("Paolo Veronese green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 155, 125],
                 Cairo::Color::PAOLO_VERONESE_GREEN.to_s)
  end

  # Papaya whip: #FFEFD5: (255, 239, 213)
  test("Papaya whip") do
    assert_equal("\#%02X%02X%02XFF" % [255, 239, 213],
                 Cairo::Color::PAPAYA_WHIP.to_s)
  end

  # Paradise pink: #E63E62: (230, 62, 98)
  test("Paradise pink") do
    assert_equal("\#%02X%02X%02XFF" % [230, 62, 98],
                 Cairo::Color::PARADISE_PINK.to_s)
  end

  # Paris Green: #50C878: (80, 200, 120)
  test("Paris Green") do
    assert_equal("\#%02X%02X%02XFF" % [80, 200, 120],
                 Cairo::Color::PARIS_GREEN.to_s)
  end

  # Parrot Pink: #D998A0: (217, 152, 160)
  test("Parrot Pink") do
    assert_equal("\#%02X%02X%02XFF" % [217, 152, 160],
                 Cairo::Color::PARROT_PINK.to_s)
  end

  # Pastel blue: #AEC6CF: (174, 198, 207)
  test("Pastel blue") do
    assert_equal("\#%02X%02X%02XFF" % [174, 198, 207],
                 Cairo::Color::PASTEL_BLUE.to_s)
  end

  # Pastel brown: #836953: (130, 105, 83)
  test("Pastel brown") do
    assert_equal("\#%02X%02X%02XFF" % [130, 105, 83],
                 Cairo::Color::PASTEL_BROWN.to_s)
  end

  # Pastel gray: #CFCFC4: (207, 207, 196)
  test("Pastel gray") do
    assert_equal("\#%02X%02X%02XFF" % [207, 207, 196],
                 Cairo::Color::PASTEL_GRAY.to_s)
  end

  # Pastel green: #77DD77: (119, 221, 119)
  test("Pastel green") do
    assert_equal("\#%02X%02X%02XFF" % [119, 221, 119],
                 Cairo::Color::PASTEL_GREEN.to_s)
  end

  # Pastel magenta: #F49AC2: (244, 154, 194)
  test("Pastel magenta") do
    assert_equal("\#%02X%02X%02XFF" % [244, 154, 194],
                 Cairo::Color::PASTEL_MAGENTA.to_s)
  end

  # Pastel orange: #FFB347: (255, 179, 71)
  test("Pastel orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 179, 71],
                 Cairo::Color::PASTEL_ORANGE.to_s)
  end

  # Pastel pink: #DEA5A4: (222, 165, 164)
  test("Pastel pink") do
    assert_equal("\#%02X%02X%02XFF" % [222, 165, 164],
                 Cairo::Color::PASTEL_PINK.to_s)
  end

  # Pastel purple: #B39EB5: (179, 158, 181)
  test("Pastel purple") do
    assert_equal("\#%02X%02X%02XFF" % [179, 158, 181],
                 Cairo::Color::PASTEL_PURPLE.to_s)
  end

  # Pastel red: #FF6961: (255, 105, 97)
  test("Pastel red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 105, 97],
                 Cairo::Color::PASTEL_RED.to_s)
  end

  # Pastel violet: #CB99C9: (203, 153, 201)
  test("Pastel violet") do
    assert_equal("\#%02X%02X%02XFF" % [203, 153, 201],
                 Cairo::Color::PASTEL_VIOLET.to_s)
  end

  # Pastel yellow: #FDFD96: (253, 253, 150)
  test("Pastel yellow") do
    assert_equal("\#%02X%02X%02XFF" % [253, 253, 150],
                 Cairo::Color::PASTEL_YELLOW.to_s)
  end

  # Patriarch: #800080: (128, 0, 128)
  test("Patriarch") do
    assert_equal("\#%02X%02X%02XFF" % [128, 0, 128],
                 Cairo::Color::PATRIARCH.to_s)
  end

  # Payne's grey: #536878: (83, 104, 120)
  test("Payne's grey") do
    assert_equal("\#%02X%02X%02XFF" % [83, 104, 120],
                 Cairo::Color::PAYNES_GREY.to_s)
  end

  # Peach: #FFE5B4: (255, 229, 180)
  test("Peach") do
    assert_equal("\#%02X%02X%02XFF" % [255, 229, 180],
                 Cairo::Color::PEACH.to_s)
  end

  # Peach (Crayola): #FFCBA4: (255, 203, 164)
  test("Peach (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 203, 164],
                 Cairo::Color::PEACH_CRAYOLA.to_s)
  end

  # Peach-orange: #FFCC99: (255, 204, 153)
  test("Peach-orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 204, 153],
                 Cairo::Color::PEACH_ORANGE.to_s)
  end

  # Peach puff: #FFDAB9: (255, 218, 185)
  test("Peach puff") do
    assert_equal("\#%02X%02X%02XFF" % [255, 218, 185],
                 Cairo::Color::PEACH_PUFF.to_s)
  end

  # Peach-yellow: #FADFAD: (250, 223, 173)
  test("Peach-yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 223, 173],
                 Cairo::Color::PEACH_YELLOW.to_s)
  end

  # Pear: #D1E231: (209, 226, 49)
  test("Pear") do
    assert_equal("\#%02X%02X%02XFF" % [209, 226, 49],
                 Cairo::Color::PEAR.to_s)
  end

  # Pearl: #EAE0C8: (234, 224, 200)
  test("Pearl") do
    assert_equal("\#%02X%02X%02XFF" % [234, 224, 200],
                 Cairo::Color::PEARL.to_s)
  end

  # Pearl Aqua: #88D8C0: (136, 216, 192)
  test("Pearl Aqua") do
    assert_equal("\#%02X%02X%02XFF" % [136, 216, 192],
                 Cairo::Color::PEARL_AQUA.to_s)
  end

  # Pearly purple: #B768A2: (183, 104, 162)
  test("Pearly purple") do
    assert_equal("\#%02X%02X%02XFF" % [183, 104, 162],
                 Cairo::Color::PEARLY_PURPLE.to_s)
  end

  # Peridot: #E6E200: (230, 226, 0)
  test("Peridot") do
    assert_equal("\#%02X%02X%02XFF" % [230, 226, 0],
                 Cairo::Color::PERIDOT.to_s)
  end

  # Periwinkle: #CCCCFF: (204, 204, 255)
  test("Periwinkle") do
    assert_equal("\#%02X%02X%02XFF" % [204, 204, 255],
                 Cairo::Color::PERIWINKLE.to_s)
  end

  # Periwinkle (Crayola): #C3CDE6: (195, 205, 230)
  test("Periwinkle (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [195, 205, 230],
                 Cairo::Color::PERIWINKLE_CRAYOLA.to_s)
  end

  # Permanent Geranium Lake: #E12C2C: (225, 44, 44)
  test("Permanent Geranium Lake") do
    assert_equal("\#%02X%02X%02XFF" % [225, 44, 44],
                 Cairo::Color::PERMANENT_GERANIUM_LAKE.to_s)
  end

  # Persian blue: #1C39BB: (28, 57, 187)
  test("Persian blue") do
    assert_equal("\#%02X%02X%02XFF" % [28, 57, 187],
                 Cairo::Color::PERSIAN_BLUE.to_s)
  end

  # Persian green: #00A693: (0, 166, 147)
  test("Persian green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 166, 147],
                 Cairo::Color::PERSIAN_GREEN.to_s)
  end

  # Persian indigo: #32127A: (50, 18, 122)
  test("Persian indigo") do
    assert_equal("\#%02X%02X%02XFF" % [50, 18, 122],
                 Cairo::Color::PERSIAN_INDIGO.to_s)
  end

  # Persian orange: #D99058: (217, 144, 88)
  test("Persian orange") do
    assert_equal("\#%02X%02X%02XFF" % [217, 144, 88],
                 Cairo::Color::PERSIAN_ORANGE.to_s)
  end

  # Persian pink: #F77FBE: (247, 127, 190)
  test("Persian pink") do
    assert_equal("\#%02X%02X%02XFF" % [247, 127, 190],
                 Cairo::Color::PERSIAN_PINK.to_s)
  end

  # Persian plum: #701C1C: (112, 28, 28)
  test("Persian plum") do
    assert_equal("\#%02X%02X%02XFF" % [112, 28, 28],
                 Cairo::Color::PERSIAN_PLUM.to_s)
  end

  # Persian red: #CC3333: (204, 51, 51)
  test("Persian red") do
    assert_equal("\#%02X%02X%02XFF" % [204, 51, 51],
                 Cairo::Color::PERSIAN_RED.to_s)
  end

  # Persian rose: #FE28A2: (254, 40, 162)
  test("Persian rose") do
    assert_equal("\#%02X%02X%02XFF" % [254, 40, 162],
                 Cairo::Color::PERSIAN_ROSE.to_s)
  end

  # Persimmon: #EC5800: (236, 88, 0)
  test("Persimmon") do
    assert_equal("\#%02X%02X%02XFF" % [236, 88, 0],
                 Cairo::Color::PERSIMMON.to_s)
  end

  # Peru: #CD853F: (205, 133, 63)
  test("Peru") do
    assert_equal("\#%02X%02X%02XFF" % [205, 133, 63],
                 Cairo::Color::PERU.to_s)
  end

  # Pewter Blue: #8BA8B7: (139, 168, 183)
  test("Pewter Blue") do
    assert_equal("\#%02X%02X%02XFF" % [139, 168, 183],
                 Cairo::Color::PEWTER_BLUE.to_s)
  end

  # Philippine blue: #0038A7: (0, 56, 167)
  test("Philippine blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 56, 167],
                 Cairo::Color::PHILIPPINE_BLUE.to_s)
  end

  # Philippine bronze: #6E3A07: (110, 58, 7)
  test("Philippine bronze") do
    assert_equal("\#%02X%02X%02XFF" % [110, 58, 7],
                 Cairo::Color::PHILIPPINE_BRONZE.to_s)
  end

  # Philippine brown: #5D1916: (93, 25, 22)
  test("Philippine brown") do
    assert_equal("\#%02X%02X%02XFF" % [93, 25, 22],
                 Cairo::Color::PHILIPPINE_BROWN.to_s)
  end

  # Philippine gold: #B17304: (177, 115, 4)
  test("Philippine gold") do
    assert_equal("\#%02X%02X%02XFF" % [177, 115, 4],
                 Cairo::Color::PHILIPPINE_GOLD.to_s)
  end

  # Philippine golden yellow: #FFDF00: (253, 223, 22)
  test("Philippine golden yellow") do
    assert_equal("\#%02X%02X%02XFF" % [253, 223, 22],
                 Cairo::Color::PHILIPPINE_GOLDEN_YELLOW.to_s)
  end

  # Philippine gray: #8C8C8C: (140, 140, 140)
  test("Philippine gray") do
    assert_equal("\#%02X%02X%02XFF" % [140, 140, 140],
                 Cairo::Color::PHILIPPINE_GRAY.to_s)
  end

  # Philippine green: #008543: (0, 133, 67)
  test("Philippine green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 133, 67],
                 Cairo::Color::PHILIPPINE_GREEN.to_s)
  end

  # Philippine indigo: #00416A: (0, 65, 106)
  test("Philippine indigo") do
    assert_equal("\#%02X%02X%02XFF" % [0, 65, 106],
                 Cairo::Color::PHILIPPINE_INDIGO.to_s)
  end

  # Philippine orange: #FF7300: (255, 115, 0)
  test("Philippine orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 115, 0],
                 Cairo::Color::PHILIPPINE_ORANGE.to_s)
  end

  # Philippine pink: #FA1A8E: (255, 26, 142)
  test("Philippine pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 26, 142],
                 Cairo::Color::PHILIPPINE_PINK.to_s)
  end

  # Philippine red: #CE1127: (206, 17, 39)
  test("Philippine red") do
    assert_equal("\#%02X%02X%02XFF" % [206, 17, 39],
                 Cairo::Color::PHILIPPINE_RED.to_s)
  end

  # Philippine silver: #B3B3B3: (179, 179, 179)
  test("Philippine silver") do
    assert_equal("\#%02X%02X%02XFF" % [179, 179, 179],
                 Cairo::Color::PHILIPPINE_SILVER.to_s)
  end

  # Philippine sky blue: #0066FF: (0, 102, 255)
  test("Philippine sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 102, 255],
                 Cairo::Color::PHILIPPINE_SKY_BLUE.to_s)
  end

  # Philippine violet: #81007F: (129, 0, 127)
  test("Philippine violet") do
    assert_equal("\#%02X%02X%02XFF" % [129, 0, 127],
                 Cairo::Color::PHILIPPINE_VIOLET.to_s)
  end

  # Philippine yellow: #FECB00: (254, 203, 0)
  test("Philippine yellow") do
    assert_equal("\#%02X%02X%02XFF" % [254, 203, 0],
                 Cairo::Color::PHILIPPINE_YELLOW.to_s)
  end

  # Phlox: #DF00FF: (223, 0, 255)
  test("Phlox") do
    assert_equal("\#%02X%02X%02XFF" % [223, 0, 255],
                 Cairo::Color::PHLOX.to_s)
  end

  # Phthalo blue: #000F89: (0, 15, 137)
  test("Phthalo blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 15, 137],
                 Cairo::Color::PHTHALO_BLUE.to_s)
  end

  # Phthalo green: #123524: (18, 53, 36)
  test("Phthalo green") do
    assert_equal("\#%02X%02X%02XFF" % [18, 53, 36],
                 Cairo::Color::PHTHALO_GREEN.to_s)
  end

  # Picton blue: #45B1E8: (69, 177, 232)
  test("Picton blue") do
    assert_equal("\#%02X%02X%02XFF" % [69, 177, 232],
                 Cairo::Color::PICTON_BLUE.to_s)
  end

  # Pictorial carmine: #C30B4E: (195, 11, 78)
  test("Pictorial carmine") do
    assert_equal("\#%02X%02X%02XFF" % [195, 11, 78],
                 Cairo::Color::PICTORIAL_CARMINE.to_s)
  end

  # Piggy pink: #FDDDE6: (253, 221, 230)
  test("Piggy pink") do
    assert_equal("\#%02X%02X%02XFF" % [253, 221, 230],
                 Cairo::Color::PIGGY_PINK.to_s)
  end

  # Pine green: #01796F: (1, 121, 111)
  test("Pine green") do
    assert_equal("\#%02X%02X%02XFF" % [1, 121, 111],
                 Cairo::Color::PINE_GREEN.to_s)
  end

  # Pine tree: #2A2F23: (42, 47, 35)
  test("Pine tree") do
    assert_equal("\#%02X%02X%02XFF" % [42, 47, 35],
                 Cairo::Color::PINE_TREE.to_s)
  end

  # Pineapple: #563C0D: (86, 60, 13)
  test("Pineapple") do
    assert_equal("\#%02X%02X%02XFF" % [86, 60, 13],
                 Cairo::Color::PINEAPPLE.to_s)
  end

  # Pink: #FFC0CB: (255, 192, 203)
  test("Pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 192, 203],
                 Cairo::Color::PINK.to_s)
  end

  # Pink (Pantone): #D74894: (215, 72, 148)
  test("Pink (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [215, 72, 148],
                 Cairo::Color::PINK_PANTONE.to_s)
  end

  # Pink Diamond (Ace Hardware Color): #F6D6DE: (246, 214, 222)
  test("Pink Diamond (Ace Hardware Color)") do
    assert_equal("\#%02X%02X%02XFF" % [246, 214, 222],
                 Cairo::Color::PINK_DIAMOND_ACE_HARDWARE_COLOR.to_s)
  end

  # Pink Diamond (Independent Retailers Colors): #F0D3DC: (240, 211, 220)
  test("Pink Diamond (Independent Retailers Colors)") do
    assert_equal("\#%02X%02X%02XFF" % [240, 211, 220],
                 Cairo::Color::PINK_DIAMOND_INDEPENDENT_RETAILERS_COLORS.to_s)
  end

  # Pink flamingo: #FC74FD: (252, 116, 253)
  test("Pink flamingo") do
    assert_equal("\#%02X%02X%02XFF" % [252, 116, 253],
                 Cairo::Color::PINK_FLAMINGO.to_s)
  end

  # Pink lace: #FFDDF4: (255, 221, 244)
  test("Pink lace") do
    assert_equal("\#%02X%02X%02XFF" % [255, 221, 244],
                 Cairo::Color::PINK_LACE.to_s)
  end

  # Pink lavender: #D8B2D1: (216, 178, 209)
  test("Pink lavender") do
    assert_equal("\#%02X%02X%02XFF" % [216, 178, 209],
                 Cairo::Color::PINK_LAVENDER.to_s)
  end

  # Pink-orange: #FF9966: (255, 153, 102)
  test("Pink-orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 102],
                 Cairo::Color::PINK_ORANGE.to_s)
  end

  # Pink pearl: #E7ACCF: (231, 172, 207)
  test("Pink pearl") do
    assert_equal("\#%02X%02X%02XFF" % [231, 172, 207],
                 Cairo::Color::PINK_PEARL.to_s)
  end

  # Pink raspberry: #980036: (152, 0, 54)
  test("Pink raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [152, 0, 54],
                 Cairo::Color::PINK_RASPBERRY.to_s)
  end

  # Pink Sherbet: #F78FA7: (247, 143, 167)
  test("Pink Sherbet") do
    assert_equal("\#%02X%02X%02XFF" % [247, 143, 167],
                 Cairo::Color::PINK_SHERBET.to_s)
  end

  # Pistachio: #93C572: (147, 197, 114)
  test("Pistachio") do
    assert_equal("\#%02X%02X%02XFF" % [147, 197, 114],
                 Cairo::Color::PISTACHIO.to_s)
  end

  # Pixie Powder: #391285: (57, 18, 133)
  test("Pixie Powder") do
    assert_equal("\#%02X%02X%02XFF" % [57, 18, 133],
                 Cairo::Color::PIXIE_POWDER.to_s)
  end

  # Platinum: #E5E4E2: (229, 228, 226)
  test("Platinum") do
    assert_equal("\#%02X%02X%02XFF" % [229, 228, 226],
                 Cairo::Color::PLATINUM.to_s)
  end

  # Plum: #8E4585: (142, 69, 133)
  test("Plum") do
    assert_equal("\#%02X%02X%02XFF" % [142, 69, 133],
                 Cairo::Color::PLUM.to_s)
  end

  # Plum (web): #DDA0DD: (221, 160, 221)
  test("Plum (web)") do
    assert_equal("\#%02X%02X%02XFF" % [221, 160, 221],
                 Cairo::Color::PLUM_WEB.to_s)
  end

  # Plump Purple: #5946B2: (89, 70, 178)
  test("Plump Purple") do
    assert_equal("\#%02X%02X%02XFF" % [89, 70, 178],
                 Cairo::Color::PLUMP_PURPLE.to_s)
  end

  # Police blue: #374F6B: (55, 79, 107)
  test("Police blue") do
    assert_equal("\#%02X%02X%02XFF" % [55, 79, 107],
                 Cairo::Color::POLICE_BLUE.to_s)
  end

  # Polished Pine: #5DA493: (93, 164, 147)
  test("Polished Pine") do
    assert_equal("\#%02X%02X%02XFF" % [93, 164, 147],
                 Cairo::Color::POLISHED_PINE.to_s)
  end

  # Pomp and Power: #86608E: (134, 96, 142)
  test("Pomp and Power") do
    assert_equal("\#%02X%02X%02XFF" % [134, 96, 142],
                 Cairo::Color::POMP_AND_POWER.to_s)
  end

  # Popstar: #BE4F62: (190, 79, 98)
  test("Popstar") do
    assert_equal("\#%02X%02X%02XFF" % [190, 79, 98],
                 Cairo::Color::POPSTAR.to_s)
  end

  # Portland Orange: #FF5A36: (255, 90, 54)
  test("Portland Orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 90, 54],
                 Cairo::Color::PORTLAND_ORANGE.to_s)
  end

  # Powder blue: #B0E0E6: (176, 224, 230)
  test("Powder blue") do
    assert_equal("\#%02X%02X%02XFF" % [176, 224, 230],
                 Cairo::Color::POWDER_BLUE.to_s)
  end

  # Prilly blue: #329CC3: (50, 156, 195)
  test("Prilly blue") do
    assert_equal("\#%02X%02X%02XFF" % [50, 156, 195],
                 Cairo::Color::PRILLY_BLUE.to_s)
  end

  # Prilly pink: #FF40A0: (255, 64, 160)
  test("Prilly pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 64, 160],
                 Cairo::Color::PRILLY_PINK.to_s)
  end

  # Prilly red: #FF0040: (255, 0, 64)
  test("Prilly red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 64],
                 Cairo::Color::PRILLY_RED.to_s)
  end

  # Princess Perfume: #FF85CF: (255, 133, 207)
  test("Princess Perfume") do
    assert_equal("\#%02X%02X%02XFF" % [255, 133, 207],
                 Cairo::Color::PRINCESS_PERFUME.to_s)
  end

  # Princeton orange: #F58025: (245, 128, 37)
  test("Princeton orange") do
    assert_equal("\#%02X%02X%02XFF" % [245, 128, 37],
                 Cairo::Color::PRINCETON_ORANGE.to_s)
  end

  # Prune: #701C1C: (112, 28, 28)
  test("Prune") do
    assert_equal("\#%02X%02X%02XFF" % [112, 28, 28],
                 Cairo::Color::PRUNE.to_s)
  end

  # Prussian blue: #003153: (0, 49, 83)
  test("Prussian blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 49, 83],
                 Cairo::Color::PRUSSIAN_BLUE.to_s)
  end

  # Psychedelic purple: #DF00FF: (223, 0, 255)
  test("Psychedelic purple") do
    assert_equal("\#%02X%02X%02XFF" % [223, 0, 255],
                 Cairo::Color::PSYCHEDELIC_PURPLE.to_s)
  end

  # Puce: #CC8899: (204, 136, 153)
  test("Puce") do
    assert_equal("\#%02X%02X%02XFF" % [204, 136, 153],
                 Cairo::Color::PUCE.to_s)
  end

  # Puce red: #722F37: (114, 47, 55)
  test("Puce red") do
    assert_equal("\#%02X%02X%02XFF" % [114, 47, 55],
                 Cairo::Color::PUCE_RED.to_s)
  end

  # Pullman Brown (UPS Brown): #644117: (100, 65, 23)
  test("Pullman Brown (UPS Brown)") do
    assert_equal("\#%02X%02X%02XFF" % [100, 65, 23],
                 Cairo::Color::PULLMAN_BROWN_UPS_BROWN.to_s)
  end

  # Pullman Green: #3B331C: (59, 51, 28)
  test("Pullman Green") do
    assert_equal("\#%02X%02X%02XFF" % [59, 51, 28],
                 Cairo::Color::PULLMAN_GREEN.to_s)
  end

  # Pumpkin: #FF7518: (255, 117, 24)
  test("Pumpkin") do
    assert_equal("\#%02X%02X%02XFF" % [255, 117, 24],
                 Cairo::Color::PUMPKIN.to_s)
  end

  # Purple (HTML): #800080: (128, 0, 128)
  test("Purple (HTML)") do
    assert_equal("\#%02X%02X%02XFF" % [128, 0, 128],
                 Cairo::Color::PURPLE_HTML.to_s)
  end

  # Purple (Munsell): #9F00C5: (159, 0, 197)
  test("Purple (Munsell)") do
    assert_equal("\#%02X%02X%02XFF" % [159, 0, 197],
                 Cairo::Color::PURPLE_MUNSELL.to_s)
  end

  # Purple (X11): #A020F0: (160, 32, 240)
  test("Purple (X11)") do
    assert_equal("\#%02X%02X%02XFF" % [160, 32, 240],
                 Cairo::Color::PURPLE_X11.to_s)
  end

  # Purple Heart: #69359C: (105, 53, 156)
  test("Purple Heart") do
    assert_equal("\#%02X%02X%02XFF" % [105, 53, 156],
                 Cairo::Color::PURPLE_HEART.to_s)
  end

  # Purple mountain majesty: #9678B6: (150, 120, 182)
  test("Purple mountain majesty") do
    assert_equal("\#%02X%02X%02XFF" % [150, 120, 182],
                 Cairo::Color::PURPLE_MOUNTAIN_MAJESTY.to_s)
  end

  # Purple navy: #4E5180: (78, 81, 128)
  test("Purple navy") do
    assert_equal("\#%02X%02X%02XFF" % [78, 81, 128],
                 Cairo::Color::PURPLE_NAVY.to_s)
  end

  # Purple pizzazz: #FE4EDA: (254, 78, 218)
  test("Purple pizzazz") do
    assert_equal("\#%02X%02X%02XFF" % [254, 78, 218],
                 Cairo::Color::PURPLE_PIZZAZZ.to_s)
  end

  # Purple Plum: #9C51B6: (156, 81, 182)
  test("Purple Plum") do
    assert_equal("\#%02X%02X%02XFF" % [156, 81, 182],
                 Cairo::Color::PURPLE_PLUM.to_s)
  end

  # Purple taupe: #50404D: (80, 64, 77)
  test("Purple taupe") do
    assert_equal("\#%02X%02X%02XFF" % [80, 64, 77],
                 Cairo::Color::PURPLE_TAUPE.to_s)
  end

  # Purpureus: #9A4EAE: (154, 78, 174)
  test("Purpureus") do
    assert_equal("\#%02X%02X%02XFF" % [154, 78, 174],
                 Cairo::Color::PURPUREUS.to_s)
  end

  # Quartz: #51484F: (81, 72, 79)
  test("Quartz") do
    assert_equal("\#%02X%02X%02XFF" % [81, 72, 79],
                 Cairo::Color::QUARTZ.to_s)
  end

  # Queen blue: #436B95: (67, 107, 149)
  test("Queen blue") do
    assert_equal("\#%02X%02X%02XFF" % [67, 107, 149],
                 Cairo::Color::QUEEN_BLUE.to_s)
  end

  # Queen pink: #E8CCD7: (232, 204, 215)
  test("Queen pink") do
    assert_equal("\#%02X%02X%02XFF" % [232, 204, 215],
                 Cairo::Color::QUEEN_PINK.to_s)
  end

  # Quick Silver: #A6A6A6: (166, 166, 166)
  test("Quick Silver") do
    assert_equal("\#%02X%02X%02XFF" % [166, 166, 166],
                 Cairo::Color::QUICK_SILVER.to_s)
  end

  # Quinacridone magenta: #8E3A59: (142, 58, 89)
  test("Quinacridone magenta") do
    assert_equal("\#%02X%02X%02XFF" % [142, 58, 89],
                 Cairo::Color::QUINACRIDONE_MAGENTA.to_s)
  end

  # Quincy: #6A5445: (106, 84, 69)
  test("Quincy") do
    assert_equal("\#%02X%02X%02XFF" % [106, 84, 69],
                 Cairo::Color::QUINCY.to_s)
  end

  # Rackley: #5D8AA8: (93, 138, 168)
  test("Rackley") do
    assert_equal("\#%02X%02X%02XFF" % [93, 138, 168],
                 Cairo::Color::RACKLEY.to_s)
  end

  # Radical Red: #FF355E: (255, 53, 94)
  test("Radical Red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 53, 94],
                 Cairo::Color::RADICAL_RED.to_s)
  end

  # Raisin black: #242124: (36, 33, 36)
  test("Raisin black") do
    assert_equal("\#%02X%02X%02XFF" % [36, 33, 36],
                 Cairo::Color::RAISIN_BLACK.to_s)
  end

  # Rajah: #FBAB60: (251, 171, 96)
  test("Rajah") do
    assert_equal("\#%02X%02X%02XFF" % [251, 171, 96],
                 Cairo::Color::RAJAH.to_s)
  end

  # Raspberry: #E30B5D: (227, 11, 92)
  test("Raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [227, 11, 92],
                 Cairo::Color::RASPBERRY.to_s)
  end

  # Raspberry glace: #915F6D: (145, 95, 109)
  test("Raspberry glace") do
    assert_equal("\#%02X%02X%02XFF" % [145, 95, 109],
                 Cairo::Color::RASPBERRY_GLACE.to_s)
  end

  # Raspberry pink: #E25098: (226, 80, 152)
  test("Raspberry pink") do
    assert_equal("\#%02X%02X%02XFF" % [226, 80, 152],
                 Cairo::Color::RASPBERRY_PINK.to_s)
  end

  # Raspberry rose: #B3446C: (179, 68, 108)
  test("Raspberry rose") do
    assert_equal("\#%02X%02X%02XFF" % [179, 68, 108],
                 Cairo::Color::RASPBERRY_ROSE.to_s)
  end

  # Raw Sienna: #D68A59: (214, 138, 89)
  test("Raw Sienna") do
    assert_equal("\#%02X%02X%02XFF" % [214, 138, 89],
                 Cairo::Color::RAW_SIENNA.to_s)
  end

  # Raw umber: #826644: (130, 102, 68)
  test("Raw umber") do
    assert_equal("\#%02X%02X%02XFF" % [130, 102, 68],
                 Cairo::Color::RAW_UMBER.to_s)
  end

  # Razzle dazzle rose: #FF33CC: (255, 51, 204)
  test("Razzle dazzle rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 51, 204],
                 Cairo::Color::RAZZLE_DAZZLE_ROSE.to_s)
  end

  # Razzmatazz: #E3256B: (227, 37, 107)
  test("Razzmatazz") do
    assert_equal("\#%02X%02X%02XFF" % [227, 37, 107],
                 Cairo::Color::RAZZMATAZZ.to_s)
  end

  # Razzmic Berry: #8D4E85: (141, 78, 133)
  test("Razzmic Berry") do
    assert_equal("\#%02X%02X%02XFF" % [141, 78, 133],
                 Cairo::Color::RAZZMIC_BERRY.to_s)
  end

  # Rebecca Purple: #663399: (102, 52, 153)
  test("Rebecca Purple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 52, 153],
                 Cairo::Color::REBECCA_PURPLE.to_s)
  end

  # Red: #FF0000: (255, 0, 0)
  test("Red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 0],
                 Cairo::Color::RED.to_s)
  end

  # Red (Crayola): #EE204D: (238, 32, 77)
  test("Red (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [238, 32, 77],
                 Cairo::Color::RED_CRAYOLA.to_s)
  end

  # Red (Munsell): #F2003C: (242, 0, 60)
  test("Red (Munsell)") do
    assert_equal("\#%02X%02X%02XFF" % [242, 0, 60],
                 Cairo::Color::RED_MUNSELL.to_s)
  end

  # Red (NCS): #C40233: (196, 2, 51)
  test("Red (NCS)") do
    assert_equal("\#%02X%02X%02XFF" % [196, 2, 51],
                 Cairo::Color::RED_NCS.to_s)
  end

  # Red (Pantone): #ED2939: (237, 41, 57)
  test("Red (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [237, 41, 57],
                 Cairo::Color::RED_PANTONE.to_s)
  end

  # Red (pigment): #ED1C24: (237, 28, 36)
  test("Red (pigment)") do
    assert_equal("\#%02X%02X%02XFF" % [237, 28, 36],
                 Cairo::Color::RED_PIGMENT.to_s)
  end

  # Red (RYB): #FE2712: (254, 39, 18)
  test("Red (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [254, 39, 18],
                 Cairo::Color::RED_RYB.to_s)
  end

  # Red-brown: #A52A2A: (165, 42, 42)
  test("Red-brown") do
    assert_equal("\#%02X%02X%02XFF" % [165, 42, 42],
                 Cairo::Color::RED_BROWN.to_s)
  end

  # Red cola: #DF0118: (223, 1, 24)
  test("Red cola") do
    assert_equal("\#%02X%02X%02XFF" % [223, 1, 24],
                 Cairo::Color::RED_COLA.to_s)
  end

  # Red devil: #860111: (134, 1, 17)
  test("Red devil") do
    assert_equal("\#%02X%02X%02XFF" % [134, 1, 17],
                 Cairo::Color::RED_DEVIL.to_s)
  end

  # Red-orange: #FF5349: (255, 83, 73)
  test("Red-orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 83, 73],
                 Cairo::Color::RED_ORANGE.to_s)
  end

  # Red-orange (Crayola): #FF681F: (255, 104, 31)
  test("Red-orange (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 104, 31],
                 Cairo::Color::RED_ORANGE_CRAYOLA.to_s)
  end

  # Red-orange (Color wheel): #FF4500: (255, 69, 0)
  test("Red-orange (Color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 69, 0],
                 Cairo::Color::RED_ORANGE_COLOR_WHEEL.to_s)
  end

  # Red-purple: #E40078: (228, 0, 120)
  test("Red-purple") do
    assert_equal("\#%02X%02X%02XFF" % [228, 0, 120],
                 Cairo::Color::RED_PURPLE.to_s)
  end

  # Red rum: #973A4A: (151, 58, 74)
  test("Red rum") do
    assert_equal("\#%02X%02X%02XFF" % [151, 58, 74],
                 Cairo::Color::RED_RUM.to_s)
  end

  # Red Salsa: #FD3A4A: (253, 58, 74)
  test("Red Salsa") do
    assert_equal("\#%02X%02X%02XFF" % [253, 58, 74],
                 Cairo::Color::RED_SALSA.to_s)
  end

  # Red strawberry: #EC0304: (236, 3, 1)
  test("Red strawberry") do
    assert_equal("\#%02X%02X%02XFF" % [236, 3, 1],
                 Cairo::Color::RED_STRAWBERRY.to_s)
  end

  # Red-violet: #C71585: (199, 21, 133)
  test("Red-violet") do
    assert_equal("\#%02X%02X%02XFF" % [199, 21, 133],
                 Cairo::Color::RED_VIOLET.to_s)
  end

  # Red-violet (Crayola): #C0448F: (192, 68, 143)
  test("Red-violet (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [192, 68, 143],
                 Cairo::Color::RED_VIOLET_CRAYOLA.to_s)
  end

  # Red-violet (Color wheel): #922B3E: (146, 43, 62)
  test("Red-violet (Color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [146, 43, 62],
                 Cairo::Color::RED_VIOLET_COLOR_WHEEL.to_s)
  end

  # Redwood: #A45A52: (164, 90, 82)
  test("Redwood") do
    assert_equal("\#%02X%02X%02XFF" % [164, 90, 82],
                 Cairo::Color::REDWOOD.to_s)
  end

  # Registration black: #000000: (0, 0, 0)
  test("Registration black") do
    assert_equal("\#%02X%02X%02XFF" % [0, 0, 0],
                 Cairo::Color::REGISTRATION_BLACK.to_s)
  end

  # Resolution blue: #002387: (0, 35, 135)
  test("Resolution blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 35, 135],
                 Cairo::Color::RESOLUTION_BLUE.to_s)
  end

  # Rhythm: #777696: (119, 118, 150)
  test("Rhythm") do
    assert_equal("\#%02X%02X%02XFF" % [119, 118, 150],
                 Cairo::Color::RHYTHM.to_s)
  end

  # Rich brilliant lavender: #F1A7FE: (241, 167, 254)
  test("Rich brilliant lavender") do
    assert_equal("\#%02X%02X%02XFF" % [241, 167, 254],
                 Cairo::Color::RICH_BRILLIANT_LAVENDER.to_s)
  end

  # Rich electric blue: #0892D0: (8, 146, 208)
  test("Rich electric blue") do
    assert_equal("\#%02X%02X%02XFF" % [8, 146, 208],
                 Cairo::Color::RICH_ELECTRIC_BLUE.to_s)
  end

  # Rich lavender: #A76BCF: (167, 107, 207)
  test("Rich lavender") do
    assert_equal("\#%02X%02X%02XFF" % [167, 107, 207],
                 Cairo::Color::RICH_LAVENDER.to_s)
  end

  # Rich lilac: #B666D2: (182, 102, 210)
  test("Rich lilac") do
    assert_equal("\#%02X%02X%02XFF" % [182, 102, 210],
                 Cairo::Color::RICH_LILAC.to_s)
  end

  # Rich maroon: #B03060: (176, 48, 96)
  test("Rich maroon") do
    assert_equal("\#%02X%02X%02XFF" % [176, 48, 96],
                 Cairo::Color::RICH_MAROON.to_s)
  end

  # Rifle green: #444C38: (68, 76, 56)
  test("Rifle green") do
    assert_equal("\#%02X%02X%02XFF" % [68, 76, 56],
                 Cairo::Color::RIFLE_GREEN.to_s)
  end

  # Ripe mango: #FFC324: (255, 195, 36)
  test("Ripe mango") do
    assert_equal("\#%02X%02X%02XFF" % [255, 195, 36],
                 Cairo::Color::RIPE_MANGO.to_s)
  end

  # Roast coffee: #704241: (112, 66, 65)
  test("Roast coffee") do
    assert_equal("\#%02X%02X%02XFF" % [112, 66, 65],
                 Cairo::Color::ROAST_COFFEE.to_s)
  end

  # Robin egg blue: #00CCCC: (0, 204, 204)
  test("Robin egg blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 204, 204],
                 Cairo::Color::ROBIN_EGG_BLUE.to_s)
  end

  # Rocket metallic: #8A7F80: (138, 127, 128)
  test("Rocket metallic") do
    assert_equal("\#%02X%02X%02XFF" % [138, 127, 128],
                 Cairo::Color::ROCKET_METALLIC.to_s)
  end

  # Roman silver: #838996: (131, 137, 150)
  test("Roman silver") do
    assert_equal("\#%02X%02X%02XFF" % [131, 137, 150],
                 Cairo::Color::ROMAN_SILVER.to_s)
  end

  # Root beer: #290E05: (41, 14, 5)
  test("Root beer") do
    assert_equal("\#%02X%02X%02XFF" % [41, 14, 5],
                 Cairo::Color::ROOT_BEER.to_s)
  end

  # Rose: #FF007F: (255, 0, 127)
  test("Rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 127],
                 Cairo::Color::ROSE.to_s)
  end

  # Rose bonbon: #F9429E: (249, 66, 158)
  test("Rose bonbon") do
    assert_equal("\#%02X%02X%02XFF" % [249, 66, 158],
                 Cairo::Color::ROSE_BONBON.to_s)
  end

  # Rose Dust: #9E5E6F: (158, 94, 111)
  test("Rose Dust") do
    assert_equal("\#%02X%02X%02XFF" % [158, 94, 111],
                 Cairo::Color::ROSE_DUST.to_s)
  end

  # Rose ebony: #674846: (103, 72, 70)
  test("Rose ebony") do
    assert_equal("\#%02X%02X%02XFF" % [103, 72, 70],
                 Cairo::Color::ROSE_EBONY.to_s)
  end

  # Rose garnet: #960145: (150, 1, 69)
  test("Rose garnet") do
    assert_equal("\#%02X%02X%02XFF" % [150, 1, 69],
                 Cairo::Color::ROSE_GARNET.to_s)
  end

  # Rose gold: #B76E79: (183, 110, 121)
  test("Rose gold") do
    assert_equal("\#%02X%02X%02XFF" % [183, 110, 121],
                 Cairo::Color::ROSE_GOLD.to_s)
  end

  # Rose madder: #E32636: (227, 38, 54)
  test("Rose madder") do
    assert_equal("\#%02X%02X%02XFF" % [227, 38, 54],
                 Cairo::Color::ROSE_MADDER.to_s)
  end

  # Rose pink: #FF66CC: (255, 102, 204)
  test("Rose pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 102, 204],
                 Cairo::Color::ROSE_PINK.to_s)
  end

  # Rose quartz: #AA98A9: (170, 152, 169)
  test("Rose quartz") do
    assert_equal("\#%02X%02X%02XFF" % [170, 152, 169],
                 Cairo::Color::ROSE_QUARTZ.to_s)
  end

  # Rose quartz pink: #BD559C: (189, 85, 156)
  test("Rose quartz pink") do
    assert_equal("\#%02X%02X%02XFF" % [189, 85, 156],
                 Cairo::Color::ROSE_QUARTZ_PINK.to_s)
  end

  # Rose red: #C21E56: (194, 30, 86)
  test("Rose red") do
    assert_equal("\#%02X%02X%02XFF" % [194, 30, 86],
                 Cairo::Color::ROSE_RED.to_s)
  end

  # Rose taupe: #905D5D: (144, 93, 93)
  test("Rose taupe") do
    assert_equal("\#%02X%02X%02XFF" % [144, 93, 93],
                 Cairo::Color::ROSE_TAUPE.to_s)
  end

  # Rose vale: #AB4E52: (171, 78, 82)
  test("Rose vale") do
    assert_equal("\#%02X%02X%02XFF" % [171, 78, 82],
                 Cairo::Color::ROSE_VALE.to_s)
  end

  # Rosewood: #65000B: (101, 0, 11)
  test("Rosewood") do
    assert_equal("\#%02X%02X%02XFF" % [101, 0, 11],
                 Cairo::Color::ROSEWOOD.to_s)
  end

  # Rosy brown: #BC8F8F: (188, 143, 143)
  test("Rosy brown") do
    assert_equal("\#%02X%02X%02XFF" % [188, 143, 143],
                 Cairo::Color::ROSY_BROWN.to_s)
  end

  # Royal azure: #0038A8: (0, 56, 168)
  test("Royal azure") do
    assert_equal("\#%02X%02X%02XFF" % [0, 56, 168],
                 Cairo::Color::ROYAL_AZURE.to_s)
  end

  # Royal blue: #002366: (0, 35, 102)
  test("Royal blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 35, 102],
                 Cairo::Color::ROYAL_BLUE.to_s)
  end

  # Royal brown: #523B35: (82, 59, 53)
  test("Royal brown") do
    assert_equal("\#%02X%02X%02XFF" % [82, 59, 53],
                 Cairo::Color::ROYAL_BROWN.to_s)
  end

  # Royal fuchsia: #CA2C92: (202, 44, 146)
  test("Royal fuchsia") do
    assert_equal("\#%02X%02X%02XFF" % [202, 44, 146],
                 Cairo::Color::ROYAL_FUCHSIA.to_s)
  end

  # Royal green: #136207: (19, 98, 7)
  test("Royal green") do
    assert_equal("\#%02X%02X%02XFF" % [19, 98, 7],
                 Cairo::Color::ROYAL_GREEN.to_s)
  end

  # Royal orange: #F99245: (249, 146, 69)
  test("Royal orange") do
    assert_equal("\#%02X%02X%02XFF" % [249, 146, 69],
                 Cairo::Color::ROYAL_ORANGE.to_s)
  end

  # Royal pink: #E73895: (231, 56, 149)
  test("Royal pink") do
    assert_equal("\#%02X%02X%02XFF" % [231, 56, 149],
                 Cairo::Color::ROYAL_PINK.to_s)
  end

  # Royal red: #9B1C31: (155, 28, 49)
  test("Royal red") do
    assert_equal("\#%02X%02X%02XFF" % [155, 28, 49],
                 Cairo::Color::ROYAL_RED.to_s)
  end

  # Royal purple: #7851A9: (120, 81, 169)
  test("Royal purple") do
    assert_equal("\#%02X%02X%02XFF" % [120, 81, 169],
                 Cairo::Color::ROYAL_PURPLE.to_s)
  end

  # Royal yellow: #FADA5E: (250, 218, 94)
  test("Royal yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 218, 94],
                 Cairo::Color::ROYAL_YELLOW.to_s)
  end

  # Ruber: #CE4676: (206, 70, 118)
  test("Ruber") do
    assert_equal("\#%02X%02X%02XFF" % [206, 70, 118],
                 Cairo::Color::RUBER.to_s)
  end

  # Rubine red: #D10056: (209, 0, 86)
  test("Rubine red") do
    assert_equal("\#%02X%02X%02XFF" % [209, 0, 86],
                 Cairo::Color::RUBINE_RED.to_s)
  end

  # Ruby: #E0115F: (224, 17, 95)
  test("Ruby") do
    assert_equal("\#%02X%02X%02XFF" % [224, 17, 95],
                 Cairo::Color::RUBY.to_s)
  end

  # Ruby red: #9B111E: (155, 17, 30)
  test("Ruby red") do
    assert_equal("\#%02X%02X%02XFF" % [155, 17, 30],
                 Cairo::Color::RUBY_RED.to_s)
  end

  # Rufous: #A81C07: (168, 28, 7)
  test("Rufous") do
    assert_equal("\#%02X%02X%02XFF" % [168, 28, 7],
                 Cairo::Color::RUFOUS.to_s)
  end

  # Rum: #9A4E40: (154, 78, 64)
  test("Rum") do
    assert_equal("\#%02X%02X%02XFF" % [154, 78, 64],
                 Cairo::Color::RUM.to_s)
  end

  # Russet: #80461B: (128, 70, 27)
  test("Russet") do
    assert_equal("\#%02X%02X%02XFF" % [128, 70, 27],
                 Cairo::Color::RUSSET.to_s)
  end

  # Russian green: #679267: (103, 146, 103)
  test("Russian green") do
    assert_equal("\#%02X%02X%02XFF" % [103, 146, 103],
                 Cairo::Color::RUSSIAN_GREEN.to_s)
  end

  # Russian violet: #32174D: (50, 23, 77)
  test("Russian violet") do
    assert_equal("\#%02X%02X%02XFF" % [50, 23, 77],
                 Cairo::Color::RUSSIAN_VIOLET.to_s)
  end

  # Rust: #B7410E: (183, 65, 14)
  test("Rust") do
    assert_equal("\#%02X%02X%02XFF" % [183, 65, 14],
                 Cairo::Color::RUST.to_s)
  end

  # Rusty red: #DA2C43: (218, 44, 67)
  test("Rusty red") do
    assert_equal("\#%02X%02X%02XFF" % [218, 44, 67],
                 Cairo::Color::RUSTY_RED.to_s)
  end

  # Sacramento State green: #043927: (4, 57, 39)
  test("Sacramento State green") do
    assert_equal("\#%02X%02X%02XFF" % [4, 57, 39],
                 Cairo::Color::SACRAMENTO_STATE_GREEN.to_s)
  end

  # Saddle brown: #8B4513: (139, 69, 19)
  test("Saddle brown") do
    assert_equal("\#%02X%02X%02XFF" % [139, 69, 19],
                 Cairo::Color::SADDLE_BROWN.to_s)
  end

  # Safety orange: #FF7800: (255, 120, 0)
  test("Safety orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 120, 0],
                 Cairo::Color::SAFETY_ORANGE.to_s)
  end

  # Safety orange (blaze orange): #FF6700: (255, 103, 0)
  test("Safety orange (blaze orange)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 103, 0],
                 Cairo::Color::SAFETY_ORANGE_BLAZE_ORANGE.to_s)
  end

  # Safety yellow: #EED202: (238, 210, 2)
  test("Safety yellow") do
    assert_equal("\#%02X%02X%02XFF" % [238, 210, 2],
                 Cairo::Color::SAFETY_YELLOW.to_s)
  end

  # Saffron: #F4C430: (244, 196, 48)
  test("Saffron") do
    assert_equal("\#%02X%02X%02XFF" % [244, 196, 48],
                 Cairo::Color::SAFFRON.to_s)
  end

  # Sage: #BCB88A: (188, 184, 138)
  test("Sage") do
    assert_equal("\#%02X%02X%02XFF" % [188, 184, 138],
                 Cairo::Color::SAGE.to_s)
  end

  # St. Patrick's blue: #23297A: (35, 41, 122)
  test("St. Patrick's blue") do
    assert_equal("\#%02X%02X%02XFF" % [35, 41, 122],
                 Cairo::Color::ST_PATRICKS_BLUE.to_s)
  end

  # Salem: #177B4D: (23, 123, 77)
  test("Salem") do
    assert_equal("\#%02X%02X%02XFF" % [23, 123, 77],
                 Cairo::Color::SALEM.to_s)
  end

  # Salmon: #FA8072: (250, 128, 114)
  test("Salmon") do
    assert_equal("\#%02X%02X%02XFF" % [250, 128, 114],
                 Cairo::Color::SALMON.to_s)
  end

  # Salmon Rose: #E7968B: (231, 150, 139)
  test("Salmon Rose") do
    assert_equal("\#%02X%02X%02XFF" % [231, 150, 139],
                 Cairo::Color::SALMON_ROSE.to_s)
  end

  # Salmon pink: #FF91A4: (255, 145, 164)
  test("Salmon pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 145, 164],
                 Cairo::Color::SALMON_PINK.to_s)
  end

  # Samsung blue: #12279E: (18, 39, 158)
  test("Samsung blue") do
    assert_equal("\#%02X%02X%02XFF" % [18, 39, 158],
                 Cairo::Color::SAMSUNG_BLUE.to_s)
  end

  # Sand: #C2B280: (194, 178, 128)
  test("Sand") do
    assert_equal("\#%02X%02X%02XFF" % [194, 178, 128],
                 Cairo::Color::SAND.to_s)
  end

  # Sand dune: #967117: (150, 113, 23)
  test("Sand dune") do
    assert_equal("\#%02X%02X%02XFF" % [150, 113, 23],
                 Cairo::Color::SAND_DUNE.to_s)
  end

  # Sandstorm: #ECD540: (236, 213, 64)
  test("Sandstorm") do
    assert_equal("\#%02X%02X%02XFF" % [236, 213, 64],
                 Cairo::Color::SANDSTORM.to_s)
  end

  # Sandy brown: #F4A460: (244, 164, 96)
  test("Sandy brown") do
    assert_equal("\#%02X%02X%02XFF" % [244, 164, 96],
                 Cairo::Color::SANDY_BROWN.to_s)
  end

  # Sandy Tan: #FDD9B5: (253, 217, 181)
  test("Sandy Tan") do
    assert_equal("\#%02X%02X%02XFF" % [253, 217, 181],
                 Cairo::Color::SANDY_TAN.to_s)
  end

  # Sandy taupe: #967117: (150, 113, 23)
  test("Sandy taupe") do
    assert_equal("\#%02X%02X%02XFF" % [150, 113, 23],
                 Cairo::Color::SANDY_TAUPE.to_s)
  end

  # Sap green: #507D2A: (80, 125, 42)
  test("Sap green") do
    assert_equal("\#%02X%02X%02XFF" % [80, 125, 42],
                 Cairo::Color::SAP_GREEN.to_s)
  end

  # Sapphire: #0F52BA: (15, 82, 186)
  test("Sapphire") do
    assert_equal("\#%02X%02X%02XFF" % [15, 82, 186],
                 Cairo::Color::SAPPHIRE.to_s)
  end

  # Sapphire blue: #0067A5: (0, 103, 165)
  test("Sapphire blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 103, 165],
                 Cairo::Color::SAPPHIRE_BLUE.to_s)
  end

  # Sasquatch Socks: #FF4681: (255, 70, 129)
  test("Sasquatch Socks") do
    assert_equal("\#%02X%02X%02XFF" % [255, 70, 129],
                 Cairo::Color::SASQUATCH_SOCKS.to_s)
  end

  # Satin sheen gold: #CBA135: (203, 161, 53)
  test("Satin sheen gold") do
    assert_equal("\#%02X%02X%02XFF" % [203, 161, 53],
                 Cairo::Color::SATIN_SHEEN_GOLD.to_s)
  end

  # Scarlet: #FF2400: (255, 36, 0)
  test("Scarlet") do
    assert_equal("\#%02X%02X%02XFF" % [255, 36, 0],
                 Cairo::Color::SCARLET.to_s)
  end

  # Schauss pink: #FF91AF: (255, 145, 175)
  test("Schauss pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 145, 175],
                 Cairo::Color::SCHAUSS_PINK.to_s)
  end

  # School bus yellow: #FFD800: (255, 216, 0)
  test("School bus yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 216, 0],
                 Cairo::Color::SCHOOL_BUS_YELLOW.to_s)
  end

  # Screamin' Green: #66FF66: (102, 255, 102)
  test("Screamin' Green") do
    assert_equal("\#%02X%02X%02XFF" % [102, 255, 102],
                 Cairo::Color::SCREAMIN_GREEN.to_s)
  end

  # Sea blue: #006994: (0, 105, 148)
  test("Sea blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 105, 148],
                 Cairo::Color::SEA_BLUE.to_s)
  end

  # Sea Foam Green: #9FE2BF: (195, 226, 191)
  test("Sea Foam Green") do
    assert_equal("\#%02X%02X%02XFF" % [195, 226, 191],
                 Cairo::Color::SEA_FOAM_GREEN.to_s)
  end

  # Sea green: #2E8B57: (46, 139, 87)
  test("Sea green") do
    assert_equal("\#%02X%02X%02XFF" % [46, 139, 87],
                 Cairo::Color::SEA_GREEN.to_s)
  end

  # Sea green (Crayola): #00FFCD: (1, 255, 205)
  test("Sea green (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [1, 255, 205],
                 Cairo::Color::SEA_GREEN_CRAYOLA.to_s)
  end

  # Sea Serpent: #4BC7CF: (75, 199, 207)
  test("Sea Serpent") do
    assert_equal("\#%02X%02X%02XFF" % [75, 199, 207],
                 Cairo::Color::SEA_SERPENT.to_s)
  end

  # Seal brown: #59260B: (50, 20, 20)
  test("Seal brown") do
    assert_equal("\#%02X%02X%02XFF" % [50, 20, 20],
                 Cairo::Color::SEAL_BROWN.to_s)
  end

  # Seashell: #FFF5EE: (255, 245, 238)
  test("Seashell") do
    assert_equal("\#%02X%02X%02XFF" % [255, 245, 238],
                 Cairo::Color::SEASHELL.to_s)
  end

  # Selective yellow: #FFBA00: (255, 186, 0)
  test("Selective yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 186, 0],
                 Cairo::Color::SELECTIVE_YELLOW.to_s)
  end

  # Sepia: #704214: (112, 66, 20)
  test("Sepia") do
    assert_equal("\#%02X%02X%02XFF" % [112, 66, 20],
                 Cairo::Color::SEPIA.to_s)
  end

  # Shadow: #8A795D: (138, 121, 93)
  test("Shadow") do
    assert_equal("\#%02X%02X%02XFF" % [138, 121, 93],
                 Cairo::Color::SHADOW.to_s)
  end

  # Shadow blue: #778BA5: (119, 139, 165)
  test("Shadow blue") do
    assert_equal("\#%02X%02X%02XFF" % [119, 139, 165],
                 Cairo::Color::SHADOW_BLUE.to_s)
  end

  # Shampoo: #FFCFF1: (255, 207, 241)
  test("Shampoo") do
    assert_equal("\#%02X%02X%02XFF" % [255, 207, 241],
                 Cairo::Color::SHAMPOO.to_s)
  end

  # Shamrock green: #009E60: (0, 158, 96)
  test("Shamrock green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 158, 96],
                 Cairo::Color::SHAMROCK_GREEN.to_s)
  end

  # Shandy: #FFE670: (255, 230, 112)
  test("Shandy") do
    assert_equal("\#%02X%02X%02XFF" % [255, 230, 112],
                 Cairo::Color::SHANDY.to_s)
  end

  # Sheen green: #8FD400: (143, 212, 0)
  test("Sheen green") do
    assert_equal("\#%02X%02X%02XFF" % [143, 212, 0],
                 Cairo::Color::SHEEN_GREEN.to_s)
  end

  # Shimmering Blush: #D98695: (217, 134, 149)
  test("Shimmering Blush") do
    assert_equal("\#%02X%02X%02XFF" % [217, 134, 149],
                 Cairo::Color::SHIMMERING_BLUSH.to_s)
  end

  # Shiny Shamrock: #5FA778: (95, 167, 120)
  test("Shiny Shamrock") do
    assert_equal("\#%02X%02X%02XFF" % [95, 167, 120],
                 Cairo::Color::SHINY_SHAMROCK.to_s)
  end

  # Shocking pink: #FC0FC0: (252, 15, 192)
  test("Shocking pink") do
    assert_equal("\#%02X%02X%02XFF" % [252, 15, 192],
                 Cairo::Color::SHOCKING_PINK.to_s)
  end

  # Shocking pink (Crayola): #FF6FFF: (255, 111, 255)
  test("Shocking pink (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 111, 255],
                 Cairo::Color::SHOCKING_PINK_CRAYOLA.to_s)
  end

  # Sienna: #882D17: (136, 45, 23)
  test("Sienna") do
    assert_equal("\#%02X%02X%02XFF" % [136, 45, 23],
                 Cairo::Color::SIENNA.to_s)
  end

  # Silver: #C0C0C0: (192, 192, 192)
  test("Silver") do
    assert_equal("\#%02X%02X%02XFF" % [192, 192, 192],
                 Cairo::Color::SILVER.to_s)
  end

  # Silver (Crayola): #C9C0BB: (201, 192, 187)
  test("Silver (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [201, 192, 187],
                 Cairo::Color::SILVER_CRAYOLA.to_s)
  end

  # Silver (Metallic): #AAA9AD: (170, 169, 173)
  test("Silver (Metallic)") do
    assert_equal("\#%02X%02X%02XFF" % [170, 169, 173],
                 Cairo::Color::SILVER_METALLIC.to_s)
  end

  # Silver chalice: #ACACAC: (172, 172, 172)
  test("Silver chalice") do
    assert_equal("\#%02X%02X%02XFF" % [172, 172, 172],
                 Cairo::Color::SILVER_CHALICE.to_s)
  end

  # Silver foil: #AFB1AE: (175, 177, 174)
  test("Silver foil") do
    assert_equal("\#%02X%02X%02XFF" % [175, 177, 174],
                 Cairo::Color::SILVER_FOIL.to_s)
  end

  # Silver Lake blue: #5D89BA: (93, 137, 186)
  test("Silver Lake blue") do
    assert_equal("\#%02X%02X%02XFF" % [93, 137, 186],
                 Cairo::Color::SILVER_LAKE_BLUE.to_s)
  end

  # Silver pink: #C4AEAD: (196, 174, 173)
  test("Silver pink") do
    assert_equal("\#%02X%02X%02XFF" % [196, 174, 173],
                 Cairo::Color::SILVER_PINK.to_s)
  end

  # Silver sand: #BFC1C2: (191, 193, 194)
  test("Silver sand") do
    assert_equal("\#%02X%02X%02XFF" % [191, 193, 194],
                 Cairo::Color::SILVER_SAND.to_s)
  end

  # Sinopia: #CB410B: (203, 65, 11)
  test("Sinopia") do
    assert_equal("\#%02X%02X%02XFF" % [203, 65, 11],
                 Cairo::Color::SINOPIA.to_s)
  end

  # Sizzling Red: #FF3855: (255, 56, 85)
  test("Sizzling Red") do
    assert_equal("\#%02X%02X%02XFF" % [255, 56, 85],
                 Cairo::Color::SIZZLING_RED.to_s)
  end

  # Sizzling Sunrise: #FFDB00: (255, 219, 0)
  test("Sizzling Sunrise") do
    assert_equal("\#%02X%02X%02XFF" % [255, 219, 0],
                 Cairo::Color::SIZZLING_SUNRISE.to_s)
  end

  # Skobeloff: #007474: (0, 116, 116)
  test("Skobeloff") do
    assert_equal("\#%02X%02X%02XFF" % [0, 116, 116],
                 Cairo::Color::SKOBELOFF.to_s)
  end

  # Sky blue: #87CEEB: (135, 206, 235)
  test("Sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [135, 206, 235],
                 Cairo::Color::SKY_BLUE.to_s)
  end

  # Sky blue (Crayola): #76D7EA: (118, 215, 234)
  test("Sky blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [118, 215, 234],
                 Cairo::Color::SKY_BLUE_CRAYOLA.to_s)
  end

  # Sky magenta: #CF71AF: (207, 113, 175)
  test("Sky magenta") do
    assert_equal("\#%02X%02X%02XFF" % [207, 113, 175],
                 Cairo::Color::SKY_MAGENTA.to_s)
  end

  # Slate blue: #6A5ACD: (106, 90, 205)
  test("Slate blue") do
    assert_equal("\#%02X%02X%02XFF" % [106, 90, 205],
                 Cairo::Color::SLATE_BLUE.to_s)
  end

  # Slate gray: #708090: (112, 128, 144)
  test("Slate gray") do
    assert_equal("\#%02X%02X%02XFF" % [112, 128, 144],
                 Cairo::Color::SLATE_GRAY.to_s)
  end

  # Slimy green: #299617: (41, 150, 23)
  test("Slimy green") do
    assert_equal("\#%02X%02X%02XFF" % [41, 150, 23],
                 Cairo::Color::SLIMY_GREEN.to_s)
  end

  # Smalt (Dark powder blue): #003399: (0, 51, 153)
  test("Smalt (Dark powder blue)") do
    assert_equal("\#%02X%02X%02XFF" % [0, 51, 153],
                 Cairo::Color::SMALT_DARK_POWDER_BLUE.to_s)
  end

  # Smashed Pumpkin: #FF6D3A: (255, 109, 58)
  test("Smashed Pumpkin") do
    assert_equal("\#%02X%02X%02XFF" % [255, 109, 58],
                 Cairo::Color::SMASHED_PUMPKIN.to_s)
  end

  # Smitten: #C84186: (200, 65, 134)
  test("Smitten") do
    assert_equal("\#%02X%02X%02XFF" % [200, 65, 134],
                 Cairo::Color::SMITTEN.to_s)
  end

  # Smoke: #738276: (115, 130, 118)
  test("Smoke") do
    assert_equal("\#%02X%02X%02XFF" % [115, 130, 118],
                 Cairo::Color::SMOKE.to_s)
  end

  # Smokey Topaz: #832A0D: (131, 42, 34)
  test("Smokey Topaz") do
    assert_equal("\#%02X%02X%02XFF" % [131, 42, 34],
                 Cairo::Color::SMOKEY_TOPAZ.to_s)
  end

  # Smoky black: #100C08: (16, 12, 8)
  test("Smoky black") do
    assert_equal("\#%02X%02X%02XFF" % [16, 12, 8],
                 Cairo::Color::SMOKY_BLACK.to_s)
  end

  # Snow: #FFFAFA: (255, 250, 250)
  test("Snow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 250, 250],
                 Cairo::Color::SNOW.to_s)
  end

  # Soap: #CEC8EF: (206, 200, 239)
  test("Soap") do
    assert_equal("\#%02X%02X%02XFF" % [206, 200, 239],
                 Cairo::Color::SOAP.to_s)
  end

  # Solid pink: #893843: (137, 56, 67)
  test("Solid pink") do
    assert_equal("\#%02X%02X%02XFF" % [137, 56, 67],
                 Cairo::Color::SOLID_PINK.to_s)
  end

  # Sonic silver: #757575: (117, 117, 117)
  test("Sonic silver") do
    assert_equal("\#%02X%02X%02XFF" % [117, 117, 117],
                 Cairo::Color::SONIC_SILVER.to_s)
  end

  # Spartan Crimson: #9E1316: (158, 19, 22)
  test("Spartan Crimson") do
    assert_equal("\#%02X%02X%02XFF" % [158, 19, 22],
                 Cairo::Color::SPARTAN_CRIMSON.to_s)
  end

  # Space cadet: #1D2951: (29, 41, 81)
  test("Space cadet") do
    assert_equal("\#%02X%02X%02XFF" % [29, 41, 81],
                 Cairo::Color::SPACE_CADET.to_s)
  end

  # Spanish bistre: #807532: (128, 117, 50)
  test("Spanish bistre") do
    assert_equal("\#%02X%02X%02XFF" % [128, 117, 50],
                 Cairo::Color::SPANISH_BISTRE.to_s)
  end

  # Spanish blue: #0070B8: (0, 112, 184)
  test("Spanish blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 112, 184],
                 Cairo::Color::SPANISH_BLUE.to_s)
  end

  # Spanish carmine: #D10047: (209, 0, 71)
  test("Spanish carmine") do
    assert_equal("\#%02X%02X%02XFF" % [209, 0, 71],
                 Cairo::Color::SPANISH_CARMINE.to_s)
  end

  # Spanish crimson: #E51A4C: (229, 26, 76)
  test("Spanish crimson") do
    assert_equal("\#%02X%02X%02XFF" % [229, 26, 76],
                 Cairo::Color::SPANISH_CRIMSON.to_s)
  end

  # Spanish gray: #989898: (152, 152, 152)
  test("Spanish gray") do
    assert_equal("\#%02X%02X%02XFF" % [152, 152, 152],
                 Cairo::Color::SPANISH_GRAY.to_s)
  end

  # Spanish green: #009150: (0, 145, 80)
  test("Spanish green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 145, 80],
                 Cairo::Color::SPANISH_GREEN.to_s)
  end

  # Spanish orange: #E86100: (232, 97, 0)
  test("Spanish orange") do
    assert_equal("\#%02X%02X%02XFF" % [232, 97, 0],
                 Cairo::Color::SPANISH_ORANGE.to_s)
  end

  # Spanish pink: #F7BFBE: (247, 191, 190)
  test("Spanish pink") do
    assert_equal("\#%02X%02X%02XFF" % [247, 191, 190],
                 Cairo::Color::SPANISH_PINK.to_s)
  end

  # Spanish purple: #66033C: (102, 3, 60)
  test("Spanish purple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 3, 60],
                 Cairo::Color::SPANISH_PURPLE.to_s)
  end

  # Spanish red: #E60026: (230, 0, 38)
  test("Spanish red") do
    assert_equal("\#%02X%02X%02XFF" % [230, 0, 38],
                 Cairo::Color::SPANISH_RED.to_s)
  end

  # Spanish sky blue: #00FFFF: (0, 255, 255)
  test("Spanish sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                 Cairo::Color::SPANISH_SKY_BLUE.to_s)
  end

  # Spanish violet: #4C2882: (76, 40, 130)
  test("Spanish violet") do
    assert_equal("\#%02X%02X%02XFF" % [76, 40, 130],
                 Cairo::Color::SPANISH_VIOLET.to_s)
  end

  # Spanish viridian: #007F5C: (0, 127, 92)
  test("Spanish viridian") do
    assert_equal("\#%02X%02X%02XFF" % [0, 127, 92],
                 Cairo::Color::SPANISH_VIRIDIAN.to_s)
  end

  # Spanish yellow: #F6B511: (246, 181, 17)
  test("Spanish yellow") do
    assert_equal("\#%02X%02X%02XFF" % [246, 181, 17],
                 Cairo::Color::SPANISH_YELLOW.to_s)
  end

  # Spicy mix: #8B5f4D: (139, 95, 77)
  test("Spicy mix") do
    assert_equal("\#%02X%02X%02XFF" % [139, 95, 77],
                 Cairo::Color::SPICY_MIX.to_s)
  end

  # Spiro Disco Ball: #0FC0FC: (15, 192, 252)
  test("Spiro Disco Ball") do
    assert_equal("\#%02X%02X%02XFF" % [15, 192, 252],
                 Cairo::Color::SPIRO_DISCO_BALL.to_s)
  end

  # Spring bud: #A7FC00: (167, 252, 0)
  test("Spring bud") do
    assert_equal("\#%02X%02X%02XFF" % [167, 252, 0],
                 Cairo::Color::SPRING_BUD.to_s)
  end

  # Spring Frost: #87FF2A: (135, 255, 42)
  test("Spring Frost") do
    assert_equal("\#%02X%02X%02XFF" % [135, 255, 42],
                 Cairo::Color::SPRING_FROST.to_s)
  end

  # Spring green: #00FF7F: (0, 255, 127)
  test("Spring green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 127],
                 Cairo::Color::SPRING_GREEN.to_s)
  end

  # Spring green (Crayola): #ECEBBD: (236, 235, 189)
  test("Spring green (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [236, 235, 189],
                 Cairo::Color::SPRING_GREEN_CRAYOLA.to_s)
  end

  # Star command blue: #007BB8: (0, 123, 184)
  test("Star command blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 123, 184],
                 Cairo::Color::STAR_COMMAND_BLUE.to_s)
  end

  # Steel blue: #4682B4: (70, 130, 180)
  test("Steel blue") do
    assert_equal("\#%02X%02X%02XFF" % [70, 130, 180],
                 Cairo::Color::STEEL_BLUE.to_s)
  end

  # Steel pink: #CC33CC: (204, 51, 204)
  test("Steel pink") do
    assert_equal("\#%02X%02X%02XFF" % [204, 51, 204],
                 Cairo::Color::STEEL_PINK.to_s)
  end

  # Steel Teal: #5F8A8B: (95, 138, 139)
  test("Steel Teal") do
    assert_equal("\#%02X%02X%02XFF" % [95, 138, 139],
                 Cairo::Color::STEEL_TEAL.to_s)
  end

  # Stil de grain yellow: #FADA5E: (250, 218, 94)
  test("Stil de grain yellow") do
    assert_equal("\#%02X%02X%02XFF" % [250, 218, 94],
                 Cairo::Color::STIL_DE_GRAIN_YELLOW.to_s)
  end

  # Straw: #E4D96F: (228, 217, 111)
  test("Straw") do
    assert_equal("\#%02X%02X%02XFF" % [228, 217, 111],
                 Cairo::Color::STRAW.to_s)
  end

  # Strawberry: #FC5A8D: (252, 90, 141)
  test("Strawberry") do
    assert_equal("\#%02X%02X%02XFF" % [252, 90, 141],
                 Cairo::Color::STRAWBERRY.to_s)
  end

  # Stop red: #CF142B: (207, 20, 43)
  test("Stop red") do
    assert_equal("\#%02X%02X%02XFF" % [207, 20, 43],
                 Cairo::Color::STOP_RED.to_s)
  end

  # Strawberry iced tea: #FC5A8D: (252, 90, 141)
  test("Strawberry iced tea") do
    assert_equal("\#%02X%02X%02XFF" % [252, 90, 141],
                 Cairo::Color::STRAWBERRY_ICED_TEA.to_s)
  end

  # Strawberry red: #C83F49: (200, 63, 73)
  test("Strawberry red") do
    assert_equal("\#%02X%02X%02XFF" % [200, 63, 73],
                 Cairo::Color::STRAWBERRY_RED.to_s)
  end

  # Sugar Plum: #914E75: (145, 78, 117)
  test("Sugar Plum") do
    assert_equal("\#%02X%02X%02XFF" % [145, 78, 117],
                 Cairo::Color::SUGAR_PLUM.to_s)
  end

  # Sunburnt Cyclops: #FF404C: (255, 64, 76)
  test("Sunburnt Cyclops") do
    assert_equal("\#%02X%02X%02XFF" % [255, 64, 76],
                 Cairo::Color::SUNBURNT_CYCLOPS.to_s)
  end

  # Sunglow: #FFCC33: (255, 204, 51)
  test("Sunglow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 204, 51],
                 Cairo::Color::SUNGLOW.to_s)
  end

  # Sunny: #F2F27A: (242, 242, 122)
  test("Sunny") do
    assert_equal("\#%02X%02X%02XFF" % [242, 242, 122],
                 Cairo::Color::SUNNY.to_s)
  end

  # Sunray: #E3AB57: (227, 171, 87)
  test("Sunray") do
    assert_equal("\#%02X%02X%02XFF" % [227, 171, 87],
                 Cairo::Color::SUNRAY.to_s)
  end

  # Sunset: #FAD6A5: (250, 214, 165)
  test("Sunset") do
    assert_equal("\#%02X%02X%02XFF" % [250, 214, 165],
                 Cairo::Color::SUNSET.to_s)
  end

  # Sunset orange: #FD5E53: (253, 94, 83)
  test("Sunset orange") do
    assert_equal("\#%02X%02X%02XFF" % [253, 94, 83],
                 Cairo::Color::SUNSET_ORANGE.to_s)
  end

  # Super pink: #CF6BA9: (207, 107, 169)
  test("Super pink") do
    assert_equal("\#%02X%02X%02XFF" % [207, 107, 169],
                 Cairo::Color::SUPER_PINK.to_s)
  end

  # Sweet Brown: #A83731: (168, 55, 49)
  test("Sweet Brown") do
    assert_equal("\#%02X%02X%02XFF" % [168, 55, 49],
                 Cairo::Color::SWEET_BROWN.to_s)
  end

  # Tan: #D2B48C: (210, 180, 140)
  test("Tan") do
    assert_equal("\#%02X%02X%02XFF" % [210, 180, 140],
                 Cairo::Color::TAN.to_s)
  end

  # Tan (Crayola): #D99A6C: (217, 154, 108)
  test("Tan (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [217, 154, 108],
                 Cairo::Color::TAN_CRAYOLA.to_s)
  end

  # Tangelo: #F94D00: (249, 77, 0)
  test("Tangelo") do
    assert_equal("\#%02X%02X%02XFF" % [249, 77, 0],
                 Cairo::Color::TANGELO.to_s)
  end

  # Tangerine: #F28500: (242, 133, 0)
  test("Tangerine") do
    assert_equal("\#%02X%02X%02XFF" % [242, 133, 0],
                 Cairo::Color::TANGERINE.to_s)
  end

  # Tangerine yellow: #FFCC00: (255, 204, 0)
  test("Tangerine yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 204, 0],
                 Cairo::Color::TANGERINE_YELLOW.to_s)
  end

  # Tango pink: #E4717A: (228, 113, 122)
  test("Tango pink") do
    assert_equal("\#%02X%02X%02XFF" % [228, 113, 122],
                 Cairo::Color::TANGO_PINK.to_s)
  end

  # Tart Orange: #FB4D46: (251, 77, 70)
  test("Tart Orange") do
    assert_equal("\#%02X%02X%02XFF" % [251, 77, 70],
                 Cairo::Color::TART_ORANGE.to_s)
  end

  # Taupe: #483C32: (72, 60, 50)
  test("Taupe") do
    assert_equal("\#%02X%02X%02XFF" % [72, 60, 50],
                 Cairo::Color::TAUPE.to_s)
  end

  # Taupe gray: #8B8589: (139, 133, 137)
  test("Taupe gray") do
    assert_equal("\#%02X%02X%02XFF" % [139, 133, 137],
                 Cairo::Color::TAUPE_GRAY.to_s)
  end

  # Tea green: #D0F0C0: (208, 240, 192)
  test("Tea green") do
    assert_equal("\#%02X%02X%02XFF" % [208, 240, 192],
                 Cairo::Color::TEA_GREEN.to_s)
  end

  # Tea rose: #F88379: (248, 131, 121)
  test("Tea rose") do
    assert_equal("\#%02X%02X%02XFF" % [248, 131, 121],
                 Cairo::Color::TEA_ROSE.to_s)
  end

  # Teal: #008080: (0, 128, 128)
  test("Teal") do
    assert_equal("\#%02X%02X%02XFF" % [0, 128, 128],
                 Cairo::Color::TEAL.to_s)
  end

  # Teal blue: #367588: (54, 117, 136)
  test("Teal blue") do
    assert_equal("\#%02X%02X%02XFF" % [54, 117, 136],
                 Cairo::Color::TEAL_BLUE.to_s)
  end

  # Teal deer: #99E6B3: (153, 230, 179)
  test("Teal deer") do
    assert_equal("\#%02X%02X%02XFF" % [153, 230, 179],
                 Cairo::Color::TEAL_DEER.to_s)
  end

  # Teal green: #00827F: (0, 130, 127)
  test("Teal green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 130, 127],
                 Cairo::Color::TEAL_GREEN.to_s)
  end

  # Telemagenta: #CF3476: (207, 52, 118)
  test("Telemagenta") do
    assert_equal("\#%02X%02X%02XFF" % [207, 52, 118],
                 Cairo::Color::TELEMAGENTA.to_s)
  end

  # Temptress: #3C2126: (60, 33, 38)
  test("Temptress") do
    assert_equal("\#%02X%02X%02XFF" % [60, 33, 38],
                 Cairo::Color::TEMPTRESS.to_s)
  end

  # Tenné (tawny): #CD5700: (205, 87, 0)
  test("Tenn\u00E9 (tawny)") do
    assert_equal("\#%02X%02X%02XFF" % [205, 87, 0],
                 Cairo::Color::TAWNY.to_s)
  end

  # Terra cotta: #E2725B: (226, 114, 91)
  test("Terra cotta") do
    assert_equal("\#%02X%02X%02XFF" % [226, 114, 91],
                 Cairo::Color::TERRA_COTTA.to_s)
  end

  # Thistle: #D8BFD8: (216, 191, 216)
  test("Thistle") do
    assert_equal("\#%02X%02X%02XFF" % [216, 191, 216],
                 Cairo::Color::THISTLE.to_s)
  end

  # Thistle (Crayola): #EBB0D7: (235, 176, 215)
  test("Thistle (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [235, 176, 215],
                 Cairo::Color::THISTLE_CRAYOLA.to_s)
  end

  # Thulian pink: #DE6FA1: (222, 111, 161)
  test("Thulian pink") do
    assert_equal("\#%02X%02X%02XFF" % [222, 111, 161],
                 Cairo::Color::THULIAN_PINK.to_s)
  end

  # Tickle Me Pink: #FC89AC: (252, 137, 172)
  test("Tickle Me Pink") do
    assert_equal("\#%02X%02X%02XFF" % [252, 137, 172],
                 Cairo::Color::TICKLE_ME_PINK.to_s)
  end

  # Tiffany Blue: #0ABAB5: (10, 186, 181)
  test("Tiffany Blue") do
    assert_equal("\#%02X%02X%02XFF" % [10, 186, 181],
                 Cairo::Color::TIFFANY_BLUE.to_s)
  end

  # Tiger's eye: #E08D3C: (224, 141, 60)
  test("Tiger's eye") do
    assert_equal("\#%02X%02X%02XFF" % [224, 141, 60],
                 Cairo::Color::TIGERS_EYE.to_s)
  end

  # Timberwolf: #DBD7D2: (219, 215, 210)
  test("Timberwolf") do
    assert_equal("\#%02X%02X%02XFF" % [219, 215, 210],
                 Cairo::Color::TIMBERWOLF.to_s)
  end

  # Titanium: #878681: (135, 134, 129)
  test("Titanium") do
    assert_equal("\#%02X%02X%02XFF" % [135, 134, 129],
                 Cairo::Color::TITANIUM.to_s)
  end

  # Titanium yellow: #EEE600: (238, 230, 0)
  test("Titanium yellow") do
    assert_equal("\#%02X%02X%02XFF" % [238, 230, 0],
                 Cairo::Color::TITANIUM_YELLOW.to_s)
  end

  # Tomato: #FF6347: (255, 99, 71)
  test("Tomato") do
    assert_equal("\#%02X%02X%02XFF" % [255, 99, 71],
                 Cairo::Color::TOMATO.to_s)
  end

  # Tomato sauce: #B21807: (178, 24, 7)
  test("Tomato sauce") do
    assert_equal("\#%02X%02X%02XFF" % [178, 24, 7],
                 Cairo::Color::TOMATO_SAUCE.to_s)
  end

  # Toolbox: #746CC0: (116, 108, 192)
  test("Toolbox") do
    assert_equal("\#%02X%02X%02XFF" % [116, 108, 192],
                 Cairo::Color::TOOLBOX.to_s)
  end

  # Tooth: #FFFAFA: (255, 250, 250)
  test("Tooth") do
    assert_equal("\#%02X%02X%02XFF" % [255, 250, 250],
                 Cairo::Color::TOOTH.to_s)
  end

  # Topaz: #FFC87C: (255, 200, 124)
  test("Topaz") do
    assert_equal("\#%02X%02X%02XFF" % [255, 200, 124],
                 Cairo::Color::TOPAZ.to_s)
  end

  # Tractor red: #FD0E35: (253, 14, 53)
  test("Tractor red") do
    assert_equal("\#%02X%02X%02XFF" % [253, 14, 53],
                 Cairo::Color::TRACTOR_RED.to_s)
  end

  # Trolley grey: #808080: (128, 128, 128)
  test("Trolley grey") do
    assert_equal("\#%02X%02X%02XFF" % [128, 128, 128],
                 Cairo::Color::TROLLEY_GREY.to_s)
  end

  # Tropical rain forest: #00755E: (0, 117, 94)
  test("Tropical rain forest") do
    assert_equal("\#%02X%02X%02XFF" % [0, 117, 94],
                 Cairo::Color::TROPICAL_RAIN_FOREST.to_s)
  end

  # Tropical violet: #CDA4DE: (205, 164, 222)
  test("Tropical violet") do
    assert_equal("\#%02X%02X%02XFF" % [205, 164, 222],
                 Cairo::Color::TROPICAL_VIOLET.to_s)
  end

  # True blue: #0073CF: (0, 115, 207)
  test("True blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 115, 207],
                 Cairo::Color::TRUE_BLUE.to_s)
  end

  # Tufts blue: #3E8EDE: (62, 142, 222)
  test("Tufts blue") do
    assert_equal("\#%02X%02X%02XFF" % [62, 142, 222],
                 Cairo::Color::TUFTS_BLUE.to_s)
  end

  # Tulip: #FF878D: (255, 135, 141)
  test("Tulip") do
    assert_equal("\#%02X%02X%02XFF" % [255, 135, 141],
                 Cairo::Color::TULIP.to_s)
  end

  # Tumbleweed: #DEAA88: (222, 170, 136)
  test("Tumbleweed") do
    assert_equal("\#%02X%02X%02XFF" % [222, 170, 136],
                 Cairo::Color::TUMBLEWEED.to_s)
  end

  # Turkish rose: #B57281: (181, 114, 129)
  test("Turkish rose") do
    assert_equal("\#%02X%02X%02XFF" % [181, 114, 129],
                 Cairo::Color::TURKISH_ROSE.to_s)
  end

  # Turquoise: #40E0D0: (64, 224, 208)
  test("Turquoise") do
    assert_equal("\#%02X%02X%02XFF" % [64, 224, 208],
                 Cairo::Color::TURQUOISE.to_s)
  end

  # Turquoise blue: #00FFEF: (0, 255, 239)
  test("Turquoise blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 255, 239],
                 Cairo::Color::TURQUOISE_BLUE.to_s)
  end

  # Turquoise green: #A0D6B4: (160, 214, 180)
  test("Turquoise green") do
    assert_equal("\#%02X%02X%02XFF" % [160, 214, 180],
                 Cairo::Color::TURQUOISE_GREEN.to_s)
  end

  # Turquoise Surf: #00C5CD: (0, 197, 205)
  test("Turquoise Surf") do
    assert_equal("\#%02X%02X%02XFF" % [0, 197, 205],
                 Cairo::Color::TURQUOISE_SURF.to_s)
  end

  # Turtle green: #8A9A5B: (138, 154, 91)
  test("Turtle green") do
    assert_equal("\#%02X%02X%02XFF" % [138, 154, 91],
                 Cairo::Color::TURTLE_GREEN.to_s)
  end

  # Tuscan: #FAD6A5: (250, 214, 165)
  test("Tuscan") do
    assert_equal("\#%02X%02X%02XFF" % [250, 214, 165],
                 Cairo::Color::TUSCAN.to_s)
  end

  # Tuscan brown: #6F4E37: (111, 78, 55)
  test("Tuscan brown") do
    assert_equal("\#%02X%02X%02XFF" % [111, 78, 55],
                 Cairo::Color::TUSCAN_BROWN.to_s)
  end

  # Tuscan red: #7C4848: (124, 72, 72)
  test("Tuscan red") do
    assert_equal("\#%02X%02X%02XFF" % [124, 72, 72],
                 Cairo::Color::TUSCAN_RED.to_s)
  end

  # Tuscan tan: #A67B5B: (166, 123, 91)
  test("Tuscan tan") do
    assert_equal("\#%02X%02X%02XFF" % [166, 123, 91],
                 Cairo::Color::TUSCAN_TAN.to_s)
  end

  # Tuscany: #C09999: (192, 153, 153)
  test("Tuscany") do
    assert_equal("\#%02X%02X%02XFF" % [192, 153, 153],
                 Cairo::Color::TUSCANY.to_s)
  end

  # Twilight lavender: #8A496B: (138, 73, 107)
  test("Twilight lavender") do
    assert_equal("\#%02X%02X%02XFF" % [138, 73, 107],
                 Cairo::Color::TWILIGHT_LAVENDER.to_s)
  end

  # Twitter blue: #26A7DE: (38, 167, 222)
  test("Twitter blue") do
    assert_equal("\#%02X%02X%02XFF" % [38, 167, 222],
                 Cairo::Color::TWITTER_BLUE.to_s)
  end

  # Tyrian purple: #66023C: (102, 2, 60)
  test("Tyrian purple") do
    assert_equal("\#%02X%02X%02XFF" % [102, 2, 60],
                 Cairo::Color::TYRIAN_PURPLE.to_s)
  end

  # Ultramarine: #3F00FF: (18, 10, 143)
  test("Ultramarine") do
    assert_equal("\#%02X%02X%02XFF" % [18, 10, 143],
                 Cairo::Color::ULTRAMARINE.to_s)
  end

  # Ultramarine blue: #4166F5: (65, 102, 245)
  test("Ultramarine blue") do
    assert_equal("\#%02X%02X%02XFF" % [65, 102, 245],
                 Cairo::Color::ULTRAMARINE_BLUE.to_s)
  end

  # Ultramarine blue (Caran d'Ache): #2111EF: (33, 17, 239)
  test("Ultramarine blue (Caran d'Ache)") do
    assert_equal("\#%02X%02X%02XFF" % [33, 17, 239],
                 Cairo::Color::ULTRAMARINE_BLUE_CARAN_DACHE.to_s)
  end

  # Ultra pink: #FF6FFF: (255, 111, 255)
  test("Ultra pink") do
    assert_equal("\#%02X%02X%02XFF" % [255, 111, 255],
                 Cairo::Color::ULTRA_PINK.to_s)
  end

  # Ultra red: #FC6C85: (252, 108, 133)
  test("Ultra red") do
    assert_equal("\#%02X%02X%02XFF" % [252, 108, 133],
                 Cairo::Color::ULTRA_RED.to_s)
  end

  # Umber: #635147: (99, 81, 71)
  test("Umber") do
    assert_equal("\#%02X%02X%02XFF" % [99, 81, 71],
                 Cairo::Color::UMBER.to_s)
  end

  # Unbleached silk: #FFDDCA: (255, 221, 202)
  test("Unbleached silk") do
    assert_equal("\#%02X%02X%02XFF" % [255, 221, 202],
                 Cairo::Color::UNBLEACHED_SILK.to_s)
  end

  # United Nations blue: #5B92E5: (91, 146, 229)
  test("United Nations blue") do
    assert_equal("\#%02X%02X%02XFF" % [91, 146, 229],
                 Cairo::Color::UNITED_NATIONS_BLUE.to_s)
  end

  # Unmellow yellow: #FFFF66: (255, 255, 102)
  test("Unmellow yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 102],
                 Cairo::Color::UNMELLOW_YELLOW.to_s)
  end

  # UP maroon: #7B1113: (123, 17, 19)
  test("UP maroon") do
    assert_equal("\#%02X%02X%02XFF" % [123, 17, 19],
                 Cairo::Color::UP_MAROON.to_s)
  end

  # Upsdell red: #AE2029: (174, 32, 41)
  test("Upsdell red") do
    assert_equal("\#%02X%02X%02XFF" % [174, 32, 41],
                 Cairo::Color::UPSDELL_RED.to_s)
  end

  # Urobilin: #E1AD21: (225, 173, 33)
  test("Urobilin") do
    assert_equal("\#%02X%02X%02XFF" % [225, 173, 33],
                 Cairo::Color::UROBILIN.to_s)
  end

  # Vampire black: #080808: (8, 8, 8)
  test("Vampire black") do
    assert_equal("\#%02X%02X%02XFF" % [8, 8, 8],
                 Cairo::Color::VAMPIRE_BLACK.to_s)
  end

  # Van Dyke brown: #664228: (102, 66, 40)
  test("Van Dyke brown") do
    assert_equal("\#%02X%02X%02XFF" % [102, 66, 40],
                 Cairo::Color::VAN_DYKE_BROWN.to_s)
  end

  # Vanilla: #F3E5AB: (243, 229, 171)
  test("Vanilla") do
    assert_equal("\#%02X%02X%02XFF" % [243, 229, 171],
                 Cairo::Color::VANILLA.to_s)
  end

  # Vanilla ice: #F38FA9: (243, 143, 169)
  test("Vanilla ice") do
    assert_equal("\#%02X%02X%02XFF" % [243, 143, 169],
                 Cairo::Color::VANILLA_ICE.to_s)
  end

  # Vegas gold: #C5B358: (197, 179, 88)
  test("Vegas gold") do
    assert_equal("\#%02X%02X%02XFF" % [197, 179, 88],
                 Cairo::Color::VEGAS_GOLD.to_s)
  end

  # Venetian red: #C80815: (200, 8, 21)
  test("Venetian red") do
    assert_equal("\#%02X%02X%02XFF" % [200, 8, 21],
                 Cairo::Color::VENETIAN_RED.to_s)
  end

  # Verdigris: #43B3AE: (67, 179, 174)
  test("Verdigris") do
    assert_equal("\#%02X%02X%02XFF" % [67, 179, 174],
                 Cairo::Color::VERDIGRIS.to_s)
  end

  # Vermilion: #E34234: (227, 66, 52)
  test("Vermilion") do
    assert_equal("\#%02X%02X%02XFF" % [227, 66, 52],
                 Cairo::Color::VERMILION.to_s)
  end

  # Veronica: #A020F0: (160, 32, 240)
  test("Veronica") do
    assert_equal("\#%02X%02X%02XFF" % [160, 32, 240],
                 Cairo::Color::VERONICA.to_s)
  end

  # Verse green: #18880d: (24, 136, 13)
  test("Verse green") do
    assert_equal("\#%02X%02X%02XFF" % [24, 136, 13],
                 Cairo::Color::VERSE_GREEN.to_s)
  end

  # Very light azure: #74BBFB: (116, 187, 251)
  test("Very light azure") do
    assert_equal("\#%02X%02X%02XFF" % [116, 187, 251],
                 Cairo::Color::VERY_LIGHT_AZURE.to_s)
  end

  # Very light blue: #6666FF: (102, 102, 255)
  test("Very light blue") do
    assert_equal("\#%02X%02X%02XFF" % [102, 102, 255],
                 Cairo::Color::VERY_LIGHT_BLUE.to_s)
  end

  # Very light malachite green: #64E986: (100, 233, 134)
  test("Very light malachite green") do
    assert_equal("\#%02X%02X%02XFF" % [100, 233, 134],
                 Cairo::Color::VERY_LIGHT_MALACHITE_GREEN.to_s)
  end

  # Very light tangelo: #FFB077: (255, 176, 119)
  test("Very light tangelo") do
    assert_equal("\#%02X%02X%02XFF" % [255, 176, 119],
                 Cairo::Color::VERY_LIGHT_TANGELO.to_s)
  end

  # Very pale orange: #FFDFBF: (255, 223, 191)
  test("Very pale orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 223, 191],
                 Cairo::Color::VERY_PALE_ORANGE.to_s)
  end

  # Very pale yellow: #FFFFBF: (255, 255, 191)
  test("Very pale yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 191],
                 Cairo::Color::VERY_PALE_YELLOW.to_s)
  end

  # Vine Green: #164010: (22, 64, 16)
  test("Vine Green") do
    assert_equal("\#%02X%02X%02XFF" % [22, 64, 16],
                 Cairo::Color::VINE_GREEN.to_s)
  end

  # Violet: #8F00FF: (143, 0, 255)
  test("Violet") do
    assert_equal("\#%02X%02X%02XFF" % [143, 0, 255],
                 Cairo::Color::VIOLET.to_s)
  end

  # Violet (Caran d'Ache): #6E00C0: (110, 0, 192)
  test("Violet (Caran d'Ache)") do
    assert_equal("\#%02X%02X%02XFF" % [110, 0, 192],
                 Cairo::Color::VIOLET_CARAN_DACHE.to_s)
  end

  # Violet (color wheel): #7F00FF: (127, 0, 255)
  test("Violet (color wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [127, 0, 255],
                 Cairo::Color::VIOLET_COLOR_WHEEL.to_s)
  end

  # Violet (crayola): #963D7F: (150, 61, 127)
  test("Violet (crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [150, 61, 127],
                 Cairo::Color::VIOLET_CRAYOLA.to_s)
  end

  # Violet (RYB): #8601AF: (134, 1, 175)
  test("Violet (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [134, 1, 175],
                 Cairo::Color::VIOLET_RYB.to_s)
  end

  # Violet (web): #EE82EE: (238, 130, 238)
  test("Violet (web)") do
    assert_equal("\#%02X%02X%02XFF" % [238, 130, 238],
                 Cairo::Color::VIOLET_WEB.to_s)
  end

  # Violet-blue: #324AB2: (50, 74, 178)
  test("Violet-blue") do
    assert_equal("\#%02X%02X%02XFF" % [50, 74, 178],
                 Cairo::Color::VIOLET_BLUE.to_s)
  end

  # Violet-blue (Crayola): #766EC8: (118, 110, 200)
  test("Violet-blue (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [118, 110, 200],
                 Cairo::Color::VIOLET_BLUE_CRAYOLA.to_s)
  end

  # Violet-red: #F75394: (247, 83, 148)
  test("Violet-red") do
    assert_equal("\#%02X%02X%02XFF" % [247, 83, 148],
                 Cairo::Color::VIOLET_RED.to_s)
  end

  # Violin Brown: #674403: (103, 68, 3)
  test("Violin Brown") do
    assert_equal("\#%02X%02X%02XFF" % [103, 68, 3],
                 Cairo::Color::VIOLIN_BROWN.to_s)
  end

  # Viridian: #40826D: (64, 130, 109)
  test("Viridian") do
    assert_equal("\#%02X%02X%02XFF" % [64, 130, 109],
                 Cairo::Color::VIRIDIAN.to_s)
  end

  # Viridian green: #009698: (0, 150, 152)
  test("Viridian green") do
    assert_equal("\#%02X%02X%02XFF" % [0, 150, 152],
                 Cairo::Color::VIRIDIAN_GREEN.to_s)
  end

  # Vista blue: #7C9ED9: (124, 158, 217)
  test("Vista blue") do
    assert_equal("\#%02X%02X%02XFF" % [124, 158, 217],
                 Cairo::Color::VISTA_BLUE.to_s)
  end

  # Vivid amber: #cc9900: (204, 153, 0)
  test("Vivid amber") do
    assert_equal("\#%02X%02X%02XFF" % [204, 153, 0],
                 Cairo::Color::VIVID_AMBER.to_s)
  end

  # Vivid auburn: #922724: (146, 39, 36)
  test("Vivid auburn") do
    assert_equal("\#%02X%02X%02XFF" % [146, 39, 36],
                 Cairo::Color::VIVID_AUBURN.to_s)
  end

  # Vivid burgundy: #9F1D35: (159, 29, 53)
  test("Vivid burgundy") do
    assert_equal("\#%02X%02X%02XFF" % [159, 29, 53],
                 Cairo::Color::VIVID_BURGUNDY.to_s)
  end

  # Vivid cerise: #DA1D81: (218, 29, 129)
  test("Vivid cerise") do
    assert_equal("\#%02X%02X%02XFF" % [218, 29, 129],
                 Cairo::Color::VIVID_CERISE.to_s)
  end

  # Vivid cerulean: #00AAEE: (0, 170, 238)
  test("Vivid cerulean") do
    assert_equal("\#%02X%02X%02XFF" % [0, 170, 238],
                 Cairo::Color::VIVID_CERULEAN.to_s)
  end

  # Vivid crimson: #CC0033: (204, 0, 51)
  test("Vivid crimson") do
    assert_equal("\#%02X%02X%02XFF" % [204, 0, 51],
                 Cairo::Color::VIVID_CRIMSON.to_s)
  end

  # Vivid gamboge: #FF9900: (255, 153, 0)
  test("Vivid gamboge") do
    assert_equal("\#%02X%02X%02XFF" % [255, 153, 0],
                 Cairo::Color::VIVID_GAMBOGE.to_s)
  end

  # Vivid lime green: #a6d608: (166, 214, 8)
  test("Vivid lime green") do
    assert_equal("\#%02X%02X%02XFF" % [166, 214, 8],
                 Cairo::Color::VIVID_LIME_GREEN.to_s)
  end

  # Vivid malachite: #00cc33: (0, 204, 51)
  test("Vivid malachite") do
    assert_equal("\#%02X%02X%02XFF" % [0, 204, 51],
                 Cairo::Color::VIVID_MALACHITE.to_s)
  end

  # Vivid mulberry: #B80CE3: (184, 12, 227)
  test("Vivid mulberry") do
    assert_equal("\#%02X%02X%02XFF" % [184, 12, 227],
                 Cairo::Color::VIVID_MULBERRY.to_s)
  end

  # Vivid orange: #FF5F00: (255, 95, 0)
  test("Vivid orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 95, 0],
                 Cairo::Color::VIVID_ORANGE.to_s)
  end

  # Vivid orange peel: #FFA000: (255, 160, 0)
  test("Vivid orange peel") do
    assert_equal("\#%02X%02X%02XFF" % [255, 160, 0],
                 Cairo::Color::VIVID_ORANGE_PEEL.to_s)
  end

  # Vivid orchid: #CC00FF: (204, 0, 255)
  test("Vivid orchid") do
    assert_equal("\#%02X%02X%02XFF" % [204, 0, 255],
                 Cairo::Color::VIVID_ORCHID.to_s)
  end

  # Vivid raspberry: #FF006C: (255, 0, 108)
  test("Vivid raspberry") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 108],
                 Cairo::Color::VIVID_RASPBERRY.to_s)
  end

  # Vivid red: #F70D1A: (247, 13, 26)
  test("Vivid red") do
    assert_equal("\#%02X%02X%02XFF" % [247, 13, 26],
                 Cairo::Color::VIVID_RED.to_s)
  end

  # Vivid red-tangelo: #DF6124: (223, 97, 36)
  test("Vivid red-tangelo") do
    assert_equal("\#%02X%02X%02XFF" % [223, 97, 36],
                 Cairo::Color::VIVID_RED_TANGELO.to_s)
  end

  # Vivid sky blue: #00CCFF: (0, 204, 255)
  test("Vivid sky blue") do
    assert_equal("\#%02X%02X%02XFF" % [0, 204, 255],
                 Cairo::Color::VIVID_SKY_BLUE.to_s)
  end

  # Vivid tangelo: #F07427: (240, 116, 39)
  test("Vivid tangelo") do
    assert_equal("\#%02X%02X%02XFF" % [240, 116, 39],
                 Cairo::Color::VIVID_TANGELO.to_s)
  end

  # Vivid tangerine: #FFA089: (255, 160, 137)
  test("Vivid tangerine") do
    assert_equal("\#%02X%02X%02XFF" % [255, 160, 137],
                 Cairo::Color::VIVID_TANGERINE.to_s)
  end

  # Vivid vermilion: #e56024: (229, 96, 36)
  test("Vivid vermilion") do
    assert_equal("\#%02X%02X%02XFF" % [229, 96, 36],
                 Cairo::Color::VIVID_VERMILION.to_s)
  end

  # Vivid violet: #9F00FF: (159, 0, 255)
  test("Vivid violet") do
    assert_equal("\#%02X%02X%02XFF" % [159, 0, 255],
                 Cairo::Color::VIVID_VIOLET.to_s)
  end

  # Vivid yellow: #FFE302: (255, 227, 2)
  test("Vivid yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 227, 2],
                 Cairo::Color::VIVID_YELLOW.to_s)
  end

  # Water: #D4F1F9: (212, 241, 249)
  test("Water") do
    assert_equal("\#%02X%02X%02XFF" % [212, 241, 249],
                 Cairo::Color::WATER.to_s)
  end

  # Watermelon: #F05C85: (240, 92, 133)
  test("Watermelon") do
    assert_equal("\#%02X%02X%02XFF" % [240, 92, 133],
                 Cairo::Color::WATERMELON.to_s)
  end

  # Watermelon red: #BF4147: (190, 65, 71)
  test("Watermelon red") do
    assert_equal("\#%02X%02X%02XFF" % [190, 65, 71],
                 Cairo::Color::WATERMELON_RED.to_s)
  end

  # Watermelon Yellow: #EEFF1B: (238, 255, 27)
  test("Watermelon Yellow") do
    assert_equal("\#%02X%02X%02XFF" % [238, 255, 27],
                 Cairo::Color::WATERMELON_YELLOW.to_s)
  end

  # Waterspout: #A4F4F9: (164, 244, 249)
  test("Waterspout") do
    assert_equal("\#%02X%02X%02XFF" % [164, 244, 249],
                 Cairo::Color::WATERSPOUT.to_s)
  end

  # Weldon Blue: #7C98AB: (124, 152, 171)
  test("Weldon Blue") do
    assert_equal("\#%02X%02X%02XFF" % [124, 152, 171],
                 Cairo::Color::WELDON_BLUE.to_s)
  end

  # Wenge: #645452: (100, 84, 82)
  test("Wenge") do
    assert_equal("\#%02X%02X%02XFF" % [100, 84, 82],
                 Cairo::Color::WENGE.to_s)
  end

  # Wheat: #F5DEB3: (245, 222, 179)
  test("Wheat") do
    assert_equal("\#%02X%02X%02XFF" % [245, 222, 179],
                 Cairo::Color::WHEAT.to_s)
  end

  # White: #FFFFFF: (255, 255, 255)
  test("White") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 255],
                 Cairo::Color::WHITE.to_s)
  end

  # White chocolate: #EDE6D6: (237, 230, 214)
  test("White chocolate") do
    assert_equal("\#%02X%02X%02XFF" % [237, 230, 214],
                 Cairo::Color::WHITE_CHOCOLATE.to_s)
  end

  # White coffee: #E6E0D4: (230, 224, 212)
  test("White coffee") do
    assert_equal("\#%02X%02X%02XFF" % [230, 224, 212],
                 Cairo::Color::WHITE_COFFEE.to_s)
  end

  # White smoke: #F5F5F5: (245, 245, 245)
  test("White smoke") do
    assert_equal("\#%02X%02X%02XFF" % [245, 245, 245],
                 Cairo::Color::WHITE_SMOKE.to_s)
  end

  # Wild orchid: #D470A2: (212, 112, 162)
  test("Wild orchid") do
    assert_equal("\#%02X%02X%02XFF" % [212, 112, 162],
                 Cairo::Color::WILD_ORCHID.to_s)
  end

  # Wild Strawberry: #FF43A4: (255, 67, 164)
  test("Wild Strawberry") do
    assert_equal("\#%02X%02X%02XFF" % [255, 67, 164],
                 Cairo::Color::WILD_STRAWBERRY.to_s)
  end

  # Wild watermelon: #FC6C85: (252, 108, 133)
  test("Wild watermelon") do
    assert_equal("\#%02X%02X%02XFF" % [252, 108, 133],
                 Cairo::Color::WILD_WATERMELON.to_s)
  end

  # Willpower orange: #FD5800: (253, 88, 0)
  test("Willpower orange") do
    assert_equal("\#%02X%02X%02XFF" % [253, 88, 0],
                 Cairo::Color::WILLPOWER_ORANGE.to_s)
  end

  # Windsor tan: #A75502: (167, 85, 2)
  test("Windsor tan") do
    assert_equal("\#%02X%02X%02XFF" % [167, 85, 2],
                 Cairo::Color::WINDSOR_TAN.to_s)
  end

  # Wine: #722F37: (114, 47, 55)
  test("Wine") do
    assert_equal("\#%02X%02X%02XFF" % [114, 47, 55],
                 Cairo::Color::WINE.to_s)
  end

  # Wine dregs: #673147: (103, 49, 71)
  test("Wine dregs") do
    assert_equal("\#%02X%02X%02XFF" % [103, 49, 71],
                 Cairo::Color::WINE_DREGS.to_s)
  end

  # Wine red: #B11226: (177, 18, 38)
  test("Wine red") do
    assert_equal("\#%02X%02X%02XFF" % [177, 18, 38],
                 Cairo::Color::WINE_RED.to_s)
  end

  # Winter Sky: #FF007C: (255, 0, 124)
  test("Winter Sky") do
    assert_equal("\#%02X%02X%02XFF" % [255, 0, 124],
                 Cairo::Color::WINTER_SKY.to_s)
  end

  # Winter Wizard: #A0E6FF: (160, 230, 255)
  test("Winter Wizard") do
    assert_equal("\#%02X%02X%02XFF" % [160, 230, 255],
                 Cairo::Color::WINTER_WIZARD.to_s)
  end

  # Wintergreen Dream: #56887D: (86, 136, 125)
  test("Wintergreen Dream") do
    assert_equal("\#%02X%02X%02XFF" % [86, 136, 125],
                 Cairo::Color::WINTERGREEN_DREAM.to_s)
  end

  # Wisteria: #C9A0DC: (201, 160, 220)
  test("Wisteria") do
    assert_equal("\#%02X%02X%02XFF" % [201, 160, 220],
                 Cairo::Color::WISTERIA.to_s)
  end

  # Wood brown: #C19A6B: (193, 154, 107)
  test("Wood brown") do
    assert_equal("\#%02X%02X%02XFF" % [193, 154, 107],
                 Cairo::Color::WOOD_BROWN.to_s)
  end

  # Xanadu: #738678: (115, 134, 120)
  test("Xanadu") do
    assert_equal("\#%02X%02X%02XFF" % [115, 134, 120],
                 Cairo::Color::XANADU.to_s)
  end

  # Yellow: #FFFF00: (255, 255, 0)
  test("Yellow") do
    assert_equal("\#%02X%02X%02XFF" % [255, 255, 0],
                 Cairo::Color::YELLOW.to_s)
  end

  # Yellow (Crayola): #FCE883: (252, 232, 131)
  test("Yellow (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [252, 232, 131],
                 Cairo::Color::YELLOW_CRAYOLA.to_s)
  end

  # Yellow (Munsell): #EFCC00: (239, 204, 0)
  test("Yellow (Munsell)") do
    assert_equal("\#%02X%02X%02XFF" % [239, 204, 0],
                 Cairo::Color::YELLOW_MUNSELL.to_s)
  end

  # Yellow (NCS): #FFD300: (255, 211, 0)
  test("Yellow (NCS)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 211, 0],
                 Cairo::Color::YELLOW_NCS.to_s)
  end

  # Yellow (Pantone): #FEDF00: (254, 223, 0)
  test("Yellow (Pantone)") do
    assert_equal("\#%02X%02X%02XFF" % [254, 223, 0],
                 Cairo::Color::YELLOW_PANTONE.to_s)
  end

  # Yellow (process): #FFEF00: (255, 239, 0)
  test("Yellow (process)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 239, 0],
                 Cairo::Color::YELLOW_PROCESS.to_s)
  end

  # Yellow (RYB): #FEFE33: (254, 254, 51)
  test("Yellow (RYB)") do
    assert_equal("\#%02X%02X%02XFF" % [254, 254, 51],
                 Cairo::Color::YELLOW_RYB.to_s)
  end

  # Yellow-green: #9ACD32: (154, 205, 50)
  test("Yellow-green") do
    assert_equal("\#%02X%02X%02XFF" % [154, 205, 50],
                 Cairo::Color::YELLOW_GREEN.to_s)
  end

  # Yellow-green (Crayola): #C5E384: (197, 227, 132)
  test("Yellow-green (Crayola)") do
    assert_equal("\#%02X%02X%02XFF" % [197, 227, 132],
                 Cairo::Color::YELLOW_GREEN_CRAYOLA.to_s)
  end

  # Yellow Orange: #FFAE42: (255, 174, 66)
  test("Yellow Orange") do
    assert_equal("\#%02X%02X%02XFF" % [255, 174, 66],
                 Cairo::Color::YELLOW_ORANGE.to_s)
  end

  # Yellow Orange (Color Wheel): #FF9505: (255, 149, 5)
  test("Yellow Orange (Color Wheel)") do
    assert_equal("\#%02X%02X%02XFF" % [255, 149, 5],
                 Cairo::Color::YELLOW_ORANGE_COLOR_WHEEL.to_s)
  end

  # Yellow rose: #FFF000: (255, 240, 0)
  test("Yellow rose") do
    assert_equal("\#%02X%02X%02XFF" % [255, 240, 0],
                 Cairo::Color::YELLOW_ROSE.to_s)
  end

  # Yellow Sunshine: #FFF700: (255, 247, 0)
  test("Yellow Sunshine") do
    assert_equal("\#%02X%02X%02XFF" % [255, 247, 0],
                 Cairo::Color::YELLOW_SUNSHINE.to_s)
  end

  # YInMn Blue: #2E5090: (46, 80, 144)
  test("YInMn Blue") do
    assert_equal("\#%02X%02X%02XFF" % [46, 80, 144],
                 Cairo::Color::YINMN_BLUE.to_s)
  end

  # Zaffre: #0014A8: (0, 20, 168)
  test("Zaffre") do
    assert_equal("\#%02X%02X%02XFF" % [0, 20, 168],
                 Cairo::Color::ZAFFRE.to_s)
  end

  # Zebra White: #F5F5F5: (245, 245, 245)
  test("Zebra White") do
    assert_equal("\#%02X%02X%02XFF" % [245, 245, 245],
                 Cairo::Color::ZEBRA_WHITE.to_s)
  end

  # Zinnwaldite: #2C1608: (44, 22, 8)
  test("Zinnwaldite") do
    assert_equal("\#%02X%02X%02XFF" % [44, 22, 8],
                 Cairo::Color::ZINNWALDITE.to_s)
  end

  class X11Test < self
    # Alice Blue: #F0F8FF: (240, 248, 255)
    test("Alice Blue") do
      assert_equal("\#%02X%02X%02XFF" % [240, 248, 255],
                   Cairo::Color::X11::ALICE_BLUE.to_s)
    end

    # Antique White: #FAEBD7: (250, 235, 215)
    test("Antique White") do
      assert_equal("\#%02X%02X%02XFF" % [250, 235, 215],
                   Cairo::Color::X11::ANTIQUE_WHITE.to_s)
    end

    # Aqua: #00FFFF: (0, 255, 255)
    test("Aqua") do
      assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                   Cairo::Color::X11::AQUA.to_s)
    end

    # Aquamarine: #7FFFD4: (127, 255, 212)
    test("Aquamarine") do
      assert_equal("\#%02X%02X%02XFF" % [127, 255, 212],
                   Cairo::Color::X11::AQUAMARINE.to_s)
    end

    # Azure: #F0FFFF: (240, 255, 255)
    test("Azure") do
      assert_equal("\#%02X%02X%02XFF" % [240, 255, 255],
                   Cairo::Color::X11::AZURE.to_s)
    end

    # Beige: #F5F5DC: (245, 245, 220)
    test("Beige") do
      assert_equal("\#%02X%02X%02XFF" % [245, 245, 220],
                   Cairo::Color::X11::BEIGE.to_s)
    end

    # Bisque: #FFE4C4: (255, 228, 196)
    test("Bisque") do
      assert_equal("\#%02X%02X%02XFF" % [255, 228, 196],
                   Cairo::Color::X11::BISQUE.to_s)
    end

    # Black: #000000: (0, 0, 0)
    test("Black") do
      assert_equal("\#%02X%02X%02XFF" % [0, 0, 0],
                   Cairo::Color::X11::BLACK.to_s)
    end

    # Blanched Almond: #FFEBCD: (255, 235, 205)
    test("Blanched Almond") do
      assert_equal("\#%02X%02X%02XFF" % [255, 235, 205],
                   Cairo::Color::X11::BLANCHED_ALMOND.to_s)
    end

    # Blue: #0000FF: (0, 0, 255)
    test("Blue") do
      assert_equal("\#%02X%02X%02XFF" % [0, 0, 255],
                   Cairo::Color::X11::BLUE.to_s)
    end

    # Blue Violet: #8A2BE2: (138, 43, 226)
    test("Blue Violet") do
      assert_equal("\#%02X%02X%02XFF" % [138, 43, 226],
                   Cairo::Color::X11::BLUE_VIOLET.to_s)
    end

    # Brown: #A52A2A: (165, 42, 42)
    test("Brown") do
      assert_equal("\#%02X%02X%02XFF" % [165, 42, 42],
                   Cairo::Color::X11::BROWN.to_s)
    end

    # Burlywood: #DEB887: (222, 184, 135)
    test("Burlywood") do
      assert_equal("\#%02X%02X%02XFF" % [222, 184, 135],
                   Cairo::Color::X11::BURLYWOOD.to_s)
    end

    # Cadet Blue: #5F9EA0: (95, 158, 160)
    test("Cadet Blue") do
      assert_equal("\#%02X%02X%02XFF" % [95, 158, 160],
                   Cairo::Color::X11::CADET_BLUE.to_s)
    end

    # Chartreuse: #7FFF00: (127, 255, 0)
    test("Chartreuse") do
      assert_equal("\#%02X%02X%02XFF" % [127, 255, 0],
                   Cairo::Color::X11::CHARTREUSE.to_s)
    end

    # Chocolate: #D2691E: (210, 105, 30)
    test("Chocolate") do
      assert_equal("\#%02X%02X%02XFF" % [210, 105, 30],
                   Cairo::Color::X11::CHOCOLATE.to_s)
    end

    # Coral: #FF7F50: (255, 127, 80)
    test("Coral") do
      assert_equal("\#%02X%02X%02XFF" % [255, 127, 80],
                   Cairo::Color::X11::CORAL.to_s)
    end

    # Cornflower Blue: #6495ED: (100, 149, 237)
    test("Cornflower Blue") do
      assert_equal("\#%02X%02X%02XFF" % [100, 149, 237],
                   Cairo::Color::X11::CORNFLOWER_BLUE.to_s)
    end

    # Cornsilk: #FFF8DC: (255, 248, 220)
    test("Cornsilk") do
      assert_equal("\#%02X%02X%02XFF" % [255, 248, 220],
                   Cairo::Color::X11::CORNSILK.to_s)
    end

    # Crimson: #DC143C: (220, 20, 60)
    test("Crimson") do
      assert_equal("\#%02X%02X%02XFF" % [220, 20, 60],
                   Cairo::Color::X11::CRIMSON.to_s)
    end

    # Cyan: #00FFFF: (0, 255, 255)
    test("Cyan") do
      assert_equal("\#%02X%02X%02XFF" % [0, 255, 255],
                   Cairo::Color::X11::CYAN.to_s)
    end

    # Dark Blue: #00008B: (0, 0, 139)
    test("Dark Blue") do
      assert_equal("\#%02X%02X%02XFF" % [0, 0, 139],
                   Cairo::Color::X11::DARK_BLUE.to_s)
    end

    # Dark Cyan: #008B8B: (0, 139, 139)
    test("Dark Cyan") do
      assert_equal("\#%02X%02X%02XFF" % [0, 139, 139],
                   Cairo::Color::X11::DARK_CYAN.to_s)
    end

    # Dark Goldenrod: #B8860B: (184, 134, 11)
    test("Dark Goldenrod") do
      assert_equal("\#%02X%02X%02XFF" % [184, 134, 11],
                   Cairo::Color::X11::DARK_GOLDENROD.to_s)
    end

    # Dark Gray: #A9A9A9: (169, 169, 169)
    test("Dark Gray") do
      assert_equal("\#%02X%02X%02XFF" % [169, 169, 169],
                   Cairo::Color::X11::DARK_GRAY.to_s)
    end

    # Dark Green: #006400: (0, 100, 0)
    test("Dark Green") do
      assert_equal("\#%02X%02X%02XFF" % [0, 100, 0],
                   Cairo::Color::X11::DARK_GREEN.to_s)
    end

    # Dark Khaki: #BDB76B: (189, 183, 107)
    test("Dark Khaki") do
      assert_equal("\#%02X%02X%02XFF" % [189, 183, 107],
                   Cairo::Color::X11::DARK_KHAKI.to_s)
    end

    # Dark Magenta: #8B008B: (139, 0, 139)
    test("Dark Magenta") do
      assert_equal("\#%02X%02X%02XFF" % [139, 0, 139],
                   Cairo::Color::X11::DARK_MAGENTA.to_s)
    end

    # Dark Olive Green: #556B2F: (85, 107, 47)
    test("Dark Olive Green") do
      assert_equal("\#%02X%02X%02XFF" % [85, 107, 47],
                   Cairo::Color::X11::DARK_OLIVE_GREEN.to_s)
    end

    # Dark Orange: #FF8C00: (255, 140, 0)
    test("Dark Orange") do
      assert_equal("\#%02X%02X%02XFF" % [255, 140, 0],
                   Cairo::Color::X11::DARK_ORANGE.to_s)
    end

    # Dark Orchid: #9932CC: (153, 50, 204)
    test("Dark Orchid") do
      assert_equal("\#%02X%02X%02XFF" % [153, 50, 204],
                   Cairo::Color::X11::DARK_ORCHID.to_s)
    end

    # Dark Red: #8B0000: (139, 0, 0)
    test("Dark Red") do
      assert_equal("\#%02X%02X%02XFF" % [139, 0, 0],
                   Cairo::Color::X11::DARK_RED.to_s)
    end

    # Dark Salmon: #E9967A: (233, 150, 122)
    test("Dark Salmon") do
      assert_equal("\#%02X%02X%02XFF" % [233, 150, 122],
                   Cairo::Color::X11::DARK_SALMON.to_s)
    end

    # Dark Sea Green: #8FBC8F: (143, 188, 143)
    test("Dark Sea Green") do
      assert_equal("\#%02X%02X%02XFF" % [143, 188, 143],
                   Cairo::Color::X11::DARK_SEA_GREEN.to_s)
    end

    # Dark Slate Blue: #483D8B: (72, 61, 139)
    test("Dark Slate Blue") do
      assert_equal("\#%02X%02X%02XFF" % [72, 61, 139],
                   Cairo::Color::X11::DARK_SLATE_BLUE.to_s)
    end

    # Dark Slate Gray: #2F4F4F: (47, 79, 79)
    test("Dark Slate Gray") do
      assert_equal("\#%02X%02X%02XFF" % [47, 79, 79],
                   Cairo::Color::X11::DARK_SLATE_GRAY.to_s)
    end

    # Dark Turquoise: #00CED1: (0, 206, 209)
    test("Dark Turquoise") do
      assert_equal("\#%02X%02X%02XFF" % [0, 206, 209],
                   Cairo::Color::X11::DARK_TURQUOISE.to_s)
    end

    # Dark Violet: #9400D3: (148, 0, 211)
    test("Dark Violet") do
      assert_equal("\#%02X%02X%02XFF" % [148, 0, 211],
                   Cairo::Color::X11::DARK_VIOLET.to_s)
    end

    # Deep Pink: #FF1493: (255, 20, 147)
    test("Deep Pink") do
      assert_equal("\#%02X%02X%02XFF" % [255, 20, 147],
                   Cairo::Color::X11::DEEP_PINK.to_s)
    end

    # Deep Sky Blue: #00BFFF: (0, 191, 255)
    test("Deep Sky Blue") do
      assert_equal("\#%02X%02X%02XFF" % [0, 191, 255],
                   Cairo::Color::X11::DEEP_SKY_BLUE.to_s)
    end

    # Dim Gray: #696969: (105, 105, 105)
    test("Dim Gray") do
      assert_equal("\#%02X%02X%02XFF" % [105, 105, 105],
                   Cairo::Color::X11::DIM_GRAY.to_s)
    end

    # Dodger Blue: #1E90FF: (30, 144, 255)
    test("Dodger Blue") do
      assert_equal("\#%02X%02X%02XFF" % [30, 144, 255],
                   Cairo::Color::X11::DODGER_BLUE.to_s)
    end

    # Firebrick: #B22222: (178, 34, 34)
    test("Firebrick") do
      assert_equal("\#%02X%02X%02XFF" % [178, 34, 34],
                   Cairo::Color::X11::FIREBRICK.to_s)
    end

    # Floral White: #FFFAF0: (255, 250, 240)
    test("Floral White") do
      assert_equal("\#%02X%02X%02XFF" % [255, 250, 240],
                   Cairo::Color::X11::FLORAL_WHITE.to_s)
    end

    # Forest Green: #228B22: (34, 139, 34)
    test("Forest Green") do
      assert_equal("\#%02X%02X%02XFF" % [34, 139, 34],
                   Cairo::Color::X11::FOREST_GREEN.to_s)
    end

    # Fuchsia: #FF00FF: (255, 0, 255)
    test("Fuchsia") do
      assert_equal("\#%02X%02X%02XFF" % [255, 0, 255],
                   Cairo::Color::X11::FUCHSIA.to_s)
    end

    # Gainsboro: #DCDCDC: (220, 220, 220)
    test("Gainsboro") do
      assert_equal("\#%02X%02X%02XFF" % [220, 220, 220],
                   Cairo::Color::X11::GAINSBORO.to_s)
    end

    # Ghost White: #F8F8FF: (248, 248, 255)
    test("Ghost White") do
      assert_equal("\#%02X%02X%02XFF" % [248, 248, 255],
                   Cairo::Color::X11::GHOST_WHITE.to_s)
    end

    # Gold: #FFD700: (255, 215, 0)
    test("Gold") do
      assert_equal("\#%02X%02X%02XFF" % [255, 215, 0],
                   Cairo::Color::X11::GOLD.to_s)
    end

    # Goldenrod: #DAA520: (218, 165, 32)
    test("Goldenrod") do
      assert_equal("\#%02X%02X%02XFF" % [218, 165, 32],
                   Cairo::Color::X11::GOLDENROD.to_s)
    end

    # Gray: #BEBEBE: (190, 190, 190)
    test("Gray") do
      assert_equal("\#%02X%02X%02XFF" % [190, 190, 190],
                   Cairo::Color::X11::GRAY.to_s)
    end

    # Web Gray: #808080: (128, 128, 128)
    test("Web Gray") do
      assert_equal("\#%02X%02X%02XFF" % [128, 128, 128],
                   Cairo::Color::X11::WEB_GRAY.to_s)
    end

    # Green: #00FF00: (0, 255, 0)
    test("Green") do
      assert_equal("\#%02X%02X%02XFF" % [0, 255, 0],
                   Cairo::Color::X11::GREEN.to_s)
    end

    # Web Green: #008000: (0, 128, 0)
    test("Web Green") do
      assert_equal("\#%02X%02X%02XFF" % [0, 128, 0],
                   Cairo::Color::X11::WEB_GREEN.to_s)
    end

    # Green Yellow: #ADFF2F: (173, 255, 47)
    test("Green Yellow") do
      assert_equal("\#%02X%02X%02XFF" % [173, 255, 47],
                   Cairo::Color::X11::GREEN_YELLOW.to_s)
    end

    # Honeydew: #F0FFF0: (240, 255, 240)
    test("Honeydew") do
      assert_equal("\#%02X%02X%02XFF" % [240, 255, 240],
                   Cairo::Color::X11::HONEYDEW.to_s)
    end

    # Hot Pink: #FF69B4: (255, 105, 180)
    test("Hot Pink") do
      assert_equal("\#%02X%02X%02XFF" % [255, 105, 180],
                   Cairo::Color::X11::HOT_PINK.to_s)
    end

    # Indian Red: #CD5C5C: (205, 92, 92)
    test("Indian Red") do
      assert_equal("\#%02X%02X%02XFF" % [205, 92, 92],
                   Cairo::Color::X11::INDIAN_RED.to_s)
    end

    # Indigo: #4B0082: (75, 0, 130)
    test("Indigo") do
      assert_equal("\#%02X%02X%02XFF" % [75, 0, 130],
                   Cairo::Color::X11::INDIGO.to_s)
    end

    # Ivory: #FFFFF0: (255, 255, 240)
    test("Ivory") do
      assert_equal("\#%02X%02X%02XFF" % [255, 255, 240],
                   Cairo::Color::X11::IVORY.to_s)
    end

    # Khaki: #F0E68C: (240, 230, 140)
    test("Khaki") do
      assert_equal("\#%02X%02X%02XFF" % [240, 230, 140],
                   Cairo::Color::X11::KHAKI.to_s)
    end

    # Lavender: #E6E6FA: (230, 230, 250)
    test("Lavender") do
      assert_equal("\#%02X%02X%02XFF" % [230, 230, 250],
                   Cairo::Color::X11::LAVENDER.to_s)
    end

    # Lavender Blush: #FFF0F5: (255, 240, 245)
    test("Lavender Blush") do
      assert_equal("\#%02X%02X%02XFF" % [255, 240, 245],
                   Cairo::Color::X11::LAVENDER_BLUSH.to_s)
    end

    # Lawn Green: #7CFC00: (124, 252, 0)
    test("Lawn Green") do
      assert_equal("\#%02X%02X%02XFF" % [124, 252, 0],
                   Cairo::Color::X11::LAWN_GREEN.to_s)
    end

    # Lemon Chiffon: #FFFACD: (255, 250, 205)
    test("Lemon Chiffon") do
      assert_equal("\#%02X%02X%02XFF" % [255, 250, 205],
                   Cairo::Color::X11::LEMON_CHIFFON.to_s)
    end

    # Light Blue: #ADD8E6: (173, 216, 230)
    test("Light Blue") do
      assert_equal("\#%02X%02X%02XFF" % [173, 216, 230],
                   Cairo::Color::X11::LIGHT_BLUE.to_s)
    end

    # Light Coral: #F08080: (240, 128, 128)
    test("Light Coral") do
      assert_equal("\#%02X%02X%02XFF" % [240, 128, 128],
                   Cairo::Color::X11::LIGHT_CORAL.to_s)
    end

    # Light Cyan: #E0FFFF: (224, 255, 255)
    test("Light Cyan") do
      assert_equal("\#%02X%02X%02XFF" % [224, 255, 255],
                   Cairo::Color::X11::LIGHT_CYAN.to_s)
    end

    # Light Goldenrod: #FAFAD2: (250, 250, 210)
    test("Light Goldenrod") do
      assert_equal("\#%02X%02X%02XFF" % [250, 250, 210],
                   Cairo::Color::X11::LIGHT_GOLDENROD.to_s)
    end

    # Light Gray: #D3D3D3: (211, 211, 211)
    test("Light Gray") do
      assert_equal("\#%02X%02X%02XFF" % [211, 211, 211],
                   Cairo::Color::X11::LIGHT_GRAY.to_s)
    end

    # Light Green: #90EE90: (144, 238, 144)
    test("Light Green") do
      assert_equal("\#%02X%02X%02XFF" % [144, 238, 144],
                   Cairo::Color::X11::LIGHT_GREEN.to_s)
    end

    # Light Pink: #FFB6C1: (255, 182, 193)
    test("Light Pink") do
      assert_equal("\#%02X%02X%02XFF" % [255, 182, 193],
                   Cairo::Color::X11::LIGHT_PINK.to_s)
    end

    # Light Salmon: #FFA07A: (255, 160, 122)
    test("Light Salmon") do
      assert_equal("\#%02X%02X%02XFF" % [255, 160, 122],
                   Cairo::Color::X11::LIGHT_SALMON.to_s)
    end

    # Light Sea Green: #20B2AA: (32, 178, 170)
    test("Light Sea Green") do
      assert_equal("\#%02X%02X%02XFF" % [32, 178, 170],
                   Cairo::Color::X11::LIGHT_SEA_GREEN.to_s)
    end

    # Light Sky Blue: #87CEFA: (135, 206, 250)
    test("Light Sky Blue") do
      assert_equal("\#%02X%02X%02XFF" % [135, 206, 250],
                   Cairo::Color::X11::LIGHT_SKY_BLUE.to_s)
    end

    # Light Slate Gray: #778899: (119, 136, 153)
    test("Light Slate Gray") do
      assert_equal("\#%02X%02X%02XFF" % [119, 136, 153],
                   Cairo::Color::X11::LIGHT_SLATE_GRAY.to_s)
    end

    # Light Steel Blue: #B0C4DE: (176, 196, 222)
    test("Light Steel Blue") do
      assert_equal("\#%02X%02X%02XFF" % [176, 196, 222],
                   Cairo::Color::X11::LIGHT_STEEL_BLUE.to_s)
    end

    # Light Yellow: #FFFFE0: (255, 255, 224)
    test("Light Yellow") do
      assert_equal("\#%02X%02X%02XFF" % [255, 255, 224],
                   Cairo::Color::X11::LIGHT_YELLOW.to_s)
    end

    # Lime: #00FF00: (0, 255, 0)
    test("Lime") do
      assert_equal("\#%02X%02X%02XFF" % [0, 255, 0],
                   Cairo::Color::X11::LIME.to_s)
    end

    # Lime Green: #32CD32: (50, 205, 50)
    test("Lime Green") do
      assert_equal("\#%02X%02X%02XFF" % [50, 205, 50],
                   Cairo::Color::X11::LIME_GREEN.to_s)
    end

    # Linen: #FAF0E6: (250, 240, 230)
    test("Linen") do
      assert_equal("\#%02X%02X%02XFF" % [250, 240, 230],
                   Cairo::Color::X11::LINEN.to_s)
    end

    # Magenta: #FF00FF: (255, 0, 255)
    test("Magenta") do
      assert_equal("\#%02X%02X%02XFF" % [255, 0, 255],
                   Cairo::Color::X11::MAGENTA.to_s)
    end

    # Maroon: #B03060: (176, 48, 96)
    test("Maroon") do
      assert_equal("\#%02X%02X%02XFF" % [176, 48, 96],
                   Cairo::Color::X11::MAROON.to_s)
    end

    # Web Maroon: #800000: (128, 0, 0)
    test("Web Maroon") do
      assert_equal("\#%02X%02X%02XFF" % [128, 0, 0],
                   Cairo::Color::X11::WEB_MAROON.to_s)
    end

    # Medium Aquamarine: #66CDAA: (102, 205, 170)
    test("Medium Aquamarine") do
      assert_equal("\#%02X%02X%02XFF" % [102, 205, 170],
                   Cairo::Color::X11::MEDIUM_AQUAMARINE.to_s)
    end

    # Medium Blue: #0000CD: (0, 0, 205)
    test("Medium Blue") do
      assert_equal("\#%02X%02X%02XFF" % [0, 0, 205],
                   Cairo::Color::X11::MEDIUM_BLUE.to_s)
    end

    # Medium Orchid: #BA55D3: (186, 85, 211)
    test("Medium Orchid") do
      assert_equal("\#%02X%02X%02XFF" % [186, 85, 211],
                   Cairo::Color::X11::MEDIUM_ORCHID.to_s)
    end

    # Medium Purple: #9370DB: (147, 112, 219)
    test("Medium Purple") do
      assert_equal("\#%02X%02X%02XFF" % [147, 112, 219],
                   Cairo::Color::X11::MEDIUM_PURPLE.to_s)
    end

    # Medium Sea Green: #3CB371: (60, 179, 113)
    test("Medium Sea Green") do
      assert_equal("\#%02X%02X%02XFF" % [60, 179, 113],
                   Cairo::Color::X11::MEDIUM_SEA_GREEN.to_s)
    end

    # Medium Slate Blue: #7B68EE: (123, 104, 238)
    test("Medium Slate Blue") do
      assert_equal("\#%02X%02X%02XFF" % [123, 104, 238],
                   Cairo::Color::X11::MEDIUM_SLATE_BLUE.to_s)
    end

    # Medium Spring Green: #00FA9A: (0, 250, 154)
    test("Medium Spring Green") do
      assert_equal("\#%02X%02X%02XFF" % [0, 250, 154],
                   Cairo::Color::X11::MEDIUM_SPRING_GREEN.to_s)
    end

    # Medium Turquoise: #48D1CC: (72, 209, 204)
    test("Medium Turquoise") do
      assert_equal("\#%02X%02X%02XFF" % [72, 209, 204],
                   Cairo::Color::X11::MEDIUM_TURQUOISE.to_s)
    end

    # Medium Violet Red: #C71585: (199, 21, 133)
    test("Medium Violet Red") do
      assert_equal("\#%02X%02X%02XFF" % [199, 21, 133],
                   Cairo::Color::X11::MEDIUM_VIOLET_RED.to_s)
    end

    # Midnight Blue: #191970: (25, 25, 112)
    test("Midnight Blue") do
      assert_equal("\#%02X%02X%02XFF" % [25, 25, 112],
                   Cairo::Color::X11::MIDNIGHT_BLUE.to_s)
    end

    # Mint Cream: #F5FFFA: (245, 255, 250)
    test("Mint Cream") do
      assert_equal("\#%02X%02X%02XFF" % [245, 255, 250],
                   Cairo::Color::X11::MINT_CREAM.to_s)
    end

    # Misty Rose: #FFE4E1: (255, 228, 225)
    test("Misty Rose") do
      assert_equal("\#%02X%02X%02XFF" % [255, 228, 225],
                   Cairo::Color::X11::MISTY_ROSE.to_s)
    end

    # Moccasin: #FFE4B5: (255, 228, 181)
    test("Moccasin") do
      assert_equal("\#%02X%02X%02XFF" % [255, 228, 181],
                   Cairo::Color::X11::MOCCASIN.to_s)
    end

    # Navajo White: #FFDEAD: (255, 222, 173)
    test("Navajo White") do
      assert_equal("\#%02X%02X%02XFF" % [255, 222, 173],
                   Cairo::Color::X11::NAVAJO_WHITE.to_s)
    end

    # Navy Blue: #000080: (0, 0, 128)
    test("Navy Blue") do
      assert_equal("\#%02X%02X%02XFF" % [0, 0, 128],
                   Cairo::Color::X11::NAVY_BLUE.to_s)
    end

    # Old Lace: #FDF5E6: (253, 245, 230)
    test("Old Lace") do
      assert_equal("\#%02X%02X%02XFF" % [253, 245, 230],
                   Cairo::Color::X11::OLD_LACE.to_s)
    end

    # Olive: #808000: (128, 128, 0)
    test("Olive") do
      assert_equal("\#%02X%02X%02XFF" % [128, 128, 0],
                   Cairo::Color::X11::OLIVE.to_s)
    end

    # Olive Drab: #6B8E23: (107, 142, 35)
    test("Olive Drab") do
      assert_equal("\#%02X%02X%02XFF" % [107, 142, 35],
                   Cairo::Color::X11::OLIVE_DRAB.to_s)
    end

    # Orange: #FFA500: (255, 165, 0)
    test("Orange") do
      assert_equal("\#%02X%02X%02XFF" % [255, 165, 0],
                   Cairo::Color::X11::ORANGE.to_s)
    end

    # Orange Red: #FF4500: (255, 69, 0)
    test("Orange Red") do
      assert_equal("\#%02X%02X%02XFF" % [255, 69, 0],
                   Cairo::Color::X11::ORANGE_RED.to_s)
    end

    # Orchid: #DA70D6: (218, 112, 214)
    test("Orchid") do
      assert_equal("\#%02X%02X%02XFF" % [218, 112, 214],
                   Cairo::Color::X11::ORCHID.to_s)
    end

    # Pale Goldenrod: #EEE8AA: (238, 232, 170)
    test("Pale Goldenrod") do
      assert_equal("\#%02X%02X%02XFF" % [238, 232, 170],
                   Cairo::Color::X11::PALE_GOLDENROD.to_s)
    end

    # Pale Green: #98FB98: (152, 251, 152)
    test("Pale Green") do
      assert_equal("\#%02X%02X%02XFF" % [152, 251, 152],
                   Cairo::Color::X11::PALE_GREEN.to_s)
    end

    # Pale Turquoise: #AFEEEE: (175, 238, 238)
    test("Pale Turquoise") do
      assert_equal("\#%02X%02X%02XFF" % [175, 238, 238],
                   Cairo::Color::X11::PALE_TURQUOISE.to_s)
    end

    # Pale Violet Red: #DB7093: (219, 112, 147)
    test("Pale Violet Red") do
      assert_equal("\#%02X%02X%02XFF" % [219, 112, 147],
                   Cairo::Color::X11::PALE_VIOLET_RED.to_s)
    end

    # Papaya Whip: #FFEFD5: (255, 239, 213)
    test("Papaya Whip") do
      assert_equal("\#%02X%02X%02XFF" % [255, 239, 213],
                   Cairo::Color::X11::PAPAYA_WHIP.to_s)
    end

    # Peach Puff: #FFDAB9: (255, 218, 185)
    test("Peach Puff") do
      assert_equal("\#%02X%02X%02XFF" % [255, 218, 185],
                   Cairo::Color::X11::PEACH_PUFF.to_s)
    end

    # Peru: #CD853F: (205, 133, 63)
    test("Peru") do
      assert_equal("\#%02X%02X%02XFF" % [205, 133, 63],
                   Cairo::Color::X11::PERU.to_s)
    end

    # Pink: #FFC0CB: (255, 192, 203)
    test("Pink") do
      assert_equal("\#%02X%02X%02XFF" % [255, 192, 203],
                   Cairo::Color::X11::PINK.to_s)
    end

    # Plum: #DDA0DD: (221, 160, 221)
    test("Plum") do
      assert_equal("\#%02X%02X%02XFF" % [221, 160, 221],
                   Cairo::Color::X11::PLUM.to_s)
    end

    # Powder Blue: #B0E0E6: (176, 224, 230)
    test("Powder Blue") do
      assert_equal("\#%02X%02X%02XFF" % [176, 224, 230],
                   Cairo::Color::X11::POWDER_BLUE.to_s)
    end

    # Purple: #A020F0: (160, 32, 240)
    test("Purple") do
      assert_equal("\#%02X%02X%02XFF" % [160, 32, 240],
                   Cairo::Color::X11::PURPLE.to_s)
    end

    # Web Purple: #800080: (128, 0, 128)
    test("Web Purple") do
      assert_equal("\#%02X%02X%02XFF" % [128, 0, 128],
                   Cairo::Color::X11::WEB_PURPLE.to_s)
    end

    # Rebecca Purple: #663399: (102, 51, 153)
    test("Rebecca Purple") do
      assert_equal("\#%02X%02X%02XFF" % [102, 51, 153],
                   Cairo::Color::X11::REBECCA_PURPLE.to_s)
    end

    # Red: #FF0000: (255, 0, 0)
    test("Red") do
      assert_equal("\#%02X%02X%02XFF" % [255, 0, 0],
                   Cairo::Color::X11::RED.to_s)
    end

    # Rosy Brown: #BC8F8F: (188, 143, 143)
    test("Rosy Brown") do
      assert_equal("\#%02X%02X%02XFF" % [188, 143, 143],
                   Cairo::Color::X11::ROSY_BROWN.to_s)
    end

    # Royal Blue: #4169E1: (65, 105, 225)
    test("Royal Blue") do
      assert_equal("\#%02X%02X%02XFF" % [65, 105, 225],
                   Cairo::Color::X11::ROYAL_BLUE.to_s)
    end

    # Saddle Brown: #8B4513: (139, 69, 19)
    test("Saddle Brown") do
      assert_equal("\#%02X%02X%02XFF" % [139, 69, 19],
                   Cairo::Color::X11::SADDLE_BROWN.to_s)
    end

    # Salmon: #FA8072: (250, 128, 114)
    test("Salmon") do
      assert_equal("\#%02X%02X%02XFF" % [250, 128, 114],
                   Cairo::Color::X11::SALMON.to_s)
    end

    # Sandy Brown: #F4A460: (244, 164, 96)
    test("Sandy Brown") do
      assert_equal("\#%02X%02X%02XFF" % [244, 164, 96],
                   Cairo::Color::X11::SANDY_BROWN.to_s)
    end

    # Sea Green: #2E8B57: (46, 139, 87)
    test("Sea Green") do
      assert_equal("\#%02X%02X%02XFF" % [46, 139, 87],
                   Cairo::Color::X11::SEA_GREEN.to_s)
    end

    # Seashell: #FFF5EE: (255, 245, 238)
    test("Seashell") do
      assert_equal("\#%02X%02X%02XFF" % [255, 245, 238],
                   Cairo::Color::X11::SEASHELL.to_s)
    end

    # Sienna: #A0522D: (160, 82, 45)
    test("Sienna") do
      assert_equal("\#%02X%02X%02XFF" % [160, 82, 45],
                   Cairo::Color::X11::SIENNA.to_s)
    end

    # Silver: #C0C0C0: (192, 192, 192)
    test("Silver") do
      assert_equal("\#%02X%02X%02XFF" % [192, 192, 192],
                   Cairo::Color::X11::SILVER.to_s)
    end

    # Sky Blue: #87CEEB: (135, 206, 235)
    test("Sky Blue") do
      assert_equal("\#%02X%02X%02XFF" % [135, 206, 235],
                   Cairo::Color::X11::SKY_BLUE.to_s)
    end

    # Slate Blue: #6A5ACD: (106, 90, 205)
    test("Slate Blue") do
      assert_equal("\#%02X%02X%02XFF" % [106, 90, 205],
                   Cairo::Color::X11::SLATE_BLUE.to_s)
    end

    # Slate Gray: #708090: (112, 128, 144)
    test("Slate Gray") do
      assert_equal("\#%02X%02X%02XFF" % [112, 128, 144],
                   Cairo::Color::X11::SLATE_GRAY.to_s)
    end

    # Snow: #FFFAFA: (255, 250, 250)
    test("Snow") do
      assert_equal("\#%02X%02X%02XFF" % [255, 250, 250],
                   Cairo::Color::X11::SNOW.to_s)
    end

    # Spring Green: #00FF7F: (0, 255, 127)
    test("Spring Green") do
      assert_equal("\#%02X%02X%02XFF" % [0, 255, 127],
                   Cairo::Color::X11::SPRING_GREEN.to_s)
    end

    # Steel Blue: #4682B4: (70, 130, 180)
    test("Steel Blue") do
      assert_equal("\#%02X%02X%02XFF" % [70, 130, 180],
                   Cairo::Color::X11::STEEL_BLUE.to_s)
    end

    # Tan: #D2B48C: (210, 180, 140)
    test("Tan") do
      assert_equal("\#%02X%02X%02XFF" % [210, 180, 140],
                   Cairo::Color::X11::TAN.to_s)
    end

    # Teal: #008080: (0, 128, 128)
    test("Teal") do
      assert_equal("\#%02X%02X%02XFF" % [0, 128, 128],
                   Cairo::Color::X11::TEAL.to_s)
    end

    # Thistle: #D8BFD8: (216, 191, 216)
    test("Thistle") do
      assert_equal("\#%02X%02X%02XFF" % [216, 191, 216],
                   Cairo::Color::X11::THISTLE.to_s)
    end

    # Tomato: #FF6347: (255, 99, 71)
    test("Tomato") do
      assert_equal("\#%02X%02X%02XFF" % [255, 99, 71],
                   Cairo::Color::X11::TOMATO.to_s)
    end

    # Turquoise: #40E0D0: (64, 224, 208)
    test("Turquoise") do
      assert_equal("\#%02X%02X%02XFF" % [64, 224, 208],
                   Cairo::Color::X11::TURQUOISE.to_s)
    end

    # Violet: #EE82EE: (238, 130, 238)
    test("Violet") do
      assert_equal("\#%02X%02X%02XFF" % [238, 130, 238],
                   Cairo::Color::X11::VIOLET.to_s)
    end

    # Wheat: #F5DEB3: (245, 222, 179)
    test("Wheat") do
      assert_equal("\#%02X%02X%02XFF" % [245, 222, 179],
                   Cairo::Color::X11::WHEAT.to_s)
    end

    # White: #FFFFFF: (255, 255, 255)
    test("White") do
      assert_equal("\#%02X%02X%02XFF" % [255, 255, 255],
                   Cairo::Color::X11::WHITE.to_s)
    end

    # White Smoke: #F5F5F5: (245, 245, 245)
    test("White Smoke") do
      assert_equal("\#%02X%02X%02XFF" % [245, 245, 245],
                   Cairo::Color::X11::WHITE_SMOKE.to_s)
    end

    # Yellow: #FFFF00: (255, 255, 0)
    test("Yellow") do
      assert_equal("\#%02X%02X%02XFF" % [255, 255, 0],
                   Cairo::Color::X11::YELLOW.to_s)
    end

    # Yellow Green: #9ACD32: (154, 205, 50)
    test("Yellow Green") do
      assert_equal("\#%02X%02X%02XFF" % [154, 205, 50],
                   Cairo::Color::X11::YELLOW_GREEN.to_s)
    end
  end
end
