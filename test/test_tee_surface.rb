class TeeSurfaceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_surface("Tee")
    only_surface("Script")
  end

  def test_new
    output1 = StringIO.new
    device1 = Cairo::ScriptDevice.new(output1)
    Cairo::ScriptSurface.create(device1, 100, 200) do |surface1|
      output2 = StringIO.new
      device2 = Cairo::ScriptDevice.new(output2)
      Cairo::ScriptSurface.create(device2, 100, 200) do |surface2|
        Cairo::TeeSurface.create(surface1) do |surface|
          surface << surface2
          Cairo::Context.create(surface) do |context|
            context.move_to(15, 30)
            context.line_to(80, 100)
            context.stroke
          end
          assert_equal(<<-SCRIPT, output1.string)
%!CairoScript
<< /content //COLOR_ALPHA /width 100 /height 200 >> surface context
n 15 30 m 80 100 l
stroke+
          SCRIPT
          assert_equal(output1.string, output2.string)
        end
      end
    end
  end
end
