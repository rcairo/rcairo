module Cairo
  class Pattern
    class << self
      def supported?(type)
        type = type.to_s.gsub(/([a-z])([A-Z])/, '\\1_\\2').downcase
        supported_predicate = "#{type}_supported?"
        return false unless respond_to?(supported_predicate)
        send(supported_predicate)
      end
    end
  end
end
