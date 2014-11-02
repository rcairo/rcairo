require 'cairo'

class ConstantsTest < Test::Unit::TestCase
  def test_text_cluster_flags
    constant_name = "TextClusterFlag"
    unless Cairo.satisfied_version?(1, 7, 6)
      assert_false(Cairo.const_defined?(constant_name))
      return
    end

    assert_true(Cairo.const_defined?(constant_name))
    assert_equal((0..1).to_a,
                 [0,
                  Cairo::TextClusterFlag::BACKWARD])
  end

  def test_new_constants_since_1_14_0
    if Cairo.satisfied_version?(1, 14, 0)
      assertion = :assert_const_defined
    else
      assertion = :assert_not_const_defined
    end
    send(assertion, Cairo::MimeType, :JBIG2)
    send(assertion, Cairo::MimeType, :JBIG2_GLOBAL)
    send(assertion, Cairo::MimeType, :JBIG2_GLOBAL_ID)
  end
end
