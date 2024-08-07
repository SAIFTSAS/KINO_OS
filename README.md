---

# Kino OS

Kino OS es un sistema operativo basado en Arduino diseñado para el proyecto Dentaku por SAIFT S.A.S. Cuenta con una interfaz gráfica de usuario (GUI) utilizando una pantalla LCD, entrada por teclado y varios módulos para operaciones aritméticas, juegos y configuración.

## Características

### Controladores

- **Controlador LCD:** Utiliza la biblioteca `LiquidCrystal_I2C` para la interfaz con una pantalla LCD de 16x2.
- **Controlador de Teclado:** Implementa la biblioteca `Keypad` para manejar la entrada de un teclado matricial de 4x4.

### Variables de Control del Programador

- **Menú Principal:** Las opciones iniciales incluyen "Aritmética", "Videojuego" y "Ajustes".
- **Menú Secundario:** Las opciones bajo "Aritmética" incluyen "Suma", "Resta", "Multiplicación" y "División".
- **Control del Menú:** Gestiona la navegación y selección dentro de los menús utilizando la pantalla LCD y el teclado.

### Unidad Aritmética (ALU)

- **Módulo ALU:** Soporta operaciones aritméticas básicas (suma, resta, multiplicación, división) y exponenciación.
- **ALU Extendida:** Capaz de realizar cálculos con múltiples operandos para escenarios aritméticos avanzados.

### Flujo de Arranque y Control

- **Inicialización:** Inicializa la pantalla LCD, muestra "KINO OS" y configura la pantalla inicial del menú.
- **Bucle Principal:** Controla el flujo del sistema operativo basado en la entrada del usuario y las selecciones del menú.
- **Gestión de Layout:** Cambia entre el menú principal, menú secundario, operaciones aritméticas, juegos y interfaces de configuración.

### Configuración y Juegos

- **Menú de Configuración:** Marcador de posición para futuras opciones de configuración.
- **Módulo de Juego:** Juego interactivo simple con mecánicas de movimiento y puntuación.

## Configuración y Uso

1. **Requisitos de Hardware:**
   - Placa Arduino compatible con las bibliotecas `Wire.h`, `LiquidCrystal_I2C.h` y `Keypad.h`.
   - Pantalla LCD de 16x2 y un teclado matricial de 4x4.

2. **Requisitos de Software:**
   - IDE de Arduino con las bibliotecas necesarias instaladas (`LiquidCrystal_I2C`, `Keypad`).

3. **Instalación:**
   - Conecta la pantalla LCD y el teclado a la placa Arduino según las configuraciones de pines definidas (`rowPins`, `colPins`).

4. **Subir Código:**
   - Sube el boceto de Arduino proporcionado (`KinoOS.ino`) a tu placa Arduino utilizando el IDE de Arduino.

5. **Uso:**
   - Al iniciar, navega por los menús utilizando el teclado (`A` para anterior, `B` para siguiente, `*` y `#` para cambios en el layout).
   - Explora las operaciones aritméticas, juega al juego o accede a los ajustes de configuración.

## Versión y Licencia

- **Versión:** 1.1.6
- **Código Abierto:** Esta es una versión de código abierto de Kino OS, disponible libremente para modificación y distribución.
- **Licencia:** Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo [LICENSE](LICENSE) para más detalles.

## Sobre Dentaku y SAIFT S.A.S.

- **Dentaku:** Kino OS fue desarrollado para el proyecto Dentaku, con el objetivo de proporcionar un sistema operativo basado en Arduino versátil.
- **SAIFT S.A.S.:** Desarrollado por SAIFT S.A.S., esta versión de Kino OS está adaptada para uso educativo y comunitario de código abierto.

## Contribuyendo

¡Las contribuciones a Kino OS son bienvenidas! No dudes en enviar informes de errores, solicitudes de características o pull requests a través de los Issues en GitHub.

---

## Kino OSS 2

Kino OSS 2 es la segunda versión del sistema operativo Kino OS, con una serie de mejoras y características nuevas:

- **Nuevas Funcionalidades:** Mejora en la lógica aritmética, soporte extendido para operaciones avanzadas y nuevas opciones en el menú.
- **Optimización del Rendimiento:** Mejoras en el manejo del menú y el rendimiento general del sistema.
- **Características Adicionales:** Nuevas opciones en el menú de configuración y ajustes experimentales.

**Versión:** 1.6.2  
**Estado:** Beta, disponible desde el 10 de agosto de 2024.  

Para más detalles y actualizaciones sobre Kino OSS 2, visita la [página oficial de SAIFT S.A.S.](https://saift-web.vercel.app/).
