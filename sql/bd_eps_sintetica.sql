--
-- Estructura de tabla para la tabla `afiliado`
--

CREATE TABLE IF NOT EXISTS `afiliado` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nombre` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definido',
  `apellido` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definido',
  `sexo` varchar(100) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definido',
  `fecha_nacimiento` date DEFAULT NULL,
  `tipo_afiliacion` varchar(100) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definida',
  `ingreso_mensual` int(11) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


--
-- Estructura de tabla para la tabla `medico`
--

CREATE TABLE IF NOT EXISTS `medico` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nombre` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definido',
  `apellido` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no definido',
  `especialidad` varchar(200) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'no tiene',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `vacunacion`
--

CREATE TABLE IF NOT EXISTS `vacunacion` (
  `id_afiliado` bigint(20) unsigned NOT NULL,
  `fecha_vacuna` date NOT NULL,
  `costo` int(11) NOT NULL DEFAULT 0,
  `nombre_vacuna` varchar(500) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'No definida',
  `efecto_secundario` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL,
  FOREIGN KEY (`id_afiliado`) REFERENCES  `afiliado`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `matricula`
--

CREATE TABLE IF NOT EXISTS `cita_medica` (
  `id_afiliado` bigint(20) unsigned NOT NULL,
  `id_medico` bigint(20) unsigned NOT NULL,
  `fecha` date NOT NULL default '1900-01-01',
  `motivo` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL,
  FOREIGN KEY (`id_afiliado`) REFERENCES  `afiliado`(`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`id_medico`) REFERENCES  `medico`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
