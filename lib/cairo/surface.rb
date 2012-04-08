module Cairo
  class Surface
    class << self
      def supported?(type)
        supported_predicate = "#{type.to_s.downcase}_supported?"
        return false unless respond_to?(supported_predicate)
        send(supported_predicate)
      end
    end
  end
end
