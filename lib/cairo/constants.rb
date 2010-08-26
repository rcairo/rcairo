module Cairo
  define_constants = Proc.new do |const_module, prefix, target|
    target ||= self
    const_module.constants.each do |const_name|
      target.const_set([prefix, const_name].compact.join("_"),
                       const_module.const_get(const_name))
    end
  end

  %w(operator antialias fill_rule line_cap line_join font_slant
     font_weight subpixel_order hint_style hint_metrics content
     format extend filter).each do |name|
    module_name = name.split(/_/).collect {|component| component.capitalize}.join
    define_constants.call(const_get(module_name), name.upcase)
  end

  define_constants.call(PathDataType, "PATH")
  define_constants.call(PathDataType, nil, Path)
  define_constants.call(SVGVersion, nil, SVGSurface)
  define_constants.call(SVGVersion, "SVG")
  if const_defined?(:TextClusterFlag)
    define_constants.call(TextClusterFlag, "TEXT_CLUSTER_FLAG")
  end
end
