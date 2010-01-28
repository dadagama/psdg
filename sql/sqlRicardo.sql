INSERT INTO `BDI`.`PSDG_fuentes` (`fue_codigo`, `fue_nombre`, `fue_es_externa`) VALUES ('8', 'Secuencial', 'f');
INSERT INTO `BDI`.`PSDG_fuentes_de_tipos` (`fdt_motor`, `fdt_tipo_de_dato`, `fdt_fue_codigo`) VALUES ('mysql', 'int', '8'), ('mysql', 'bigint', '8');
INSERT INTO `BDI`.`PSDG_fuentes_de_tipos` (`fdt_motor`, `fdt_tipo_de_dato`, `fdt_fue_codigo`) VALUES ('mysql', 'timestamp', '8');
INSERT INTO `BDI`.`PSDG_fuentes_de_tipos` (`fdt_motor`, `fdt_tipo_de_dato`, `fdt_fue_codigo`) VALUES ('mysql', 'date', '8');
INSERT INTO `BDI`.`PSDG_idioma` (`idi_texto`, `idi_lenguaje`, `idi_traduccion`) VALUES ('rec_lbl_valor_secuencial', 'es', 'Valor inicial'), ('rec_lbl_valor_secuencial', 'en', 'Initial value');
INSERT INTO `BDI`.`PSDG_idioma` (`idi_texto`, `idi_lenguaje`, `idi_traduccion`) VALUES ('rec_lbl_delta_secuencial', 'es', 'Delta'), ('rec_lbl_delta_secuencial', 'en', 'Delta');
