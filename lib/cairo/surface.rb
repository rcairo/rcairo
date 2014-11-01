module Cairo
  class Surface
    class << self
      def supported?(type)
        type_components = type.to_s.split(/([A-Z][a-z\d]+)/).reject(&:empty?)
        snake_case_type_name = type_components.join("_").downcase
        supported_predicate = "#{snake_case_type_name}_supported?"
        return false unless respond_to?(supported_predicate)
        send(supported_predicate)
      end
    end
  end
end
