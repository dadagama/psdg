--
-- Estructura de tabla para la tabla `escuela`
--

CREATE TABLE IF NOT EXISTS `escuela` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nombre` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `ciudad` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `departamento` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `direccion` varchar(200) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

--
-- Volcar la base de datos para la tabla `escuela`
--


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `estudiante`
--

CREATE TABLE IF NOT EXISTS `estudiante` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nombre` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `apellido` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `fecha_nacimiento` date NOT NULL,
  `ciudad_nacimiento` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `ciudad_vive` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

--
-- Volcar la base de datos para la tabla `estudiante`
--


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `matricula`
--

CREATE TABLE IF NOT EXISTS `matricula` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `id_estudiante` bigint(20) unsigned NOT NULL,
  `id_escuela` bigint(20) unsigned NOT NULL,
  `curso` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `feccha_matricula` date NOT NULL,
    PRIMARY KEY (`id`),
  FOREIGN KEY (`id_estudiante`) REFERENCES  `estudiante`(`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`id_escuela`) REFERENCES  `escuela`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;



-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `estimulo_matricula`
--

CREATE TABLE IF NOT EXISTS `estimulo_matricula` (
  `id_matricula` bigint(20) unsigned NOT NULL,
  `descuento` int(11) NOT NULL,
  FOREIGN KEY (`id_matricula`) REFERENCES  `matricula`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `aulas_por_escuela`
--

CREATE TABLE IF NOT EXISTS `aulas_por_escuela` (
  `id_escuela` bigint(20) unsigned NOT NULL,
   `num_aulas` int(11) NOT NULL,
  FOREIGN KEY (`id_escuela`) REFERENCES  `escuela`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


