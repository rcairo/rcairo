require 'cairo'

class ExceptionTest < Test::Unit::TestCase
  def test_new_symbols_since_1_7_2
    if Cairo.satisfied_version?(1, 7, 2)
      assertion = :assert_defined
    else
      assertion = :assert_not_defined
    end
    send(assertion, "FontTypeMismatch")
    send(assertion, "UserFontImmutable")
    send(assertion, "UserFontError")
    send(assertion, "NegativeCount")
    send(assertion, "InvalidClusters")
    send(assertion, "InvalidSlant")
    send(assertion, "InvalidWeight")
  end

  def test_new_symbols_since_1_14_0
    if Cairo.satisfied_version?(1, 14, 0)
      assertion = :assert_defined
    else
      assertion = :assert_not_defined
    end
    send(assertion, "JBIG2GlobalMissing")
  end

  private
  def assert_defined(name)
    assert_true(Cairo.const_defined?(name))
  end

  def assert_not_defined(name)
    assert_false(Cairo.const_defined?(name))
  end
end
