# Proyecto Final – Gestor de Procesos  
**Materia:** Estructuras de Datos  
**Lenguaje:** C++ (estándar C++17)

## Enunciado del Proyecto
**SISTEMA DE CONTROL Y SEGUIMIENTO DE PROCESOS**
Desarrollar un sistema que simule la gestión y ejecución de procesos que ingresan al sistema y deben ser atendidos siguiendo un flujo determinado. Cada proceso debe contar con un identificador, un estado y la información necesaria para su seguimiento. 
El sistema debe permitir registrar nuevos procesos, almacenarlos de manera ordenada y ejecutarlos respetando el orden en el que fueron ingresados. A medida que los procesos se ejecutan, el sistema debe actualizar su estado y registrar el historial de ejecuciones, permitiendo revisar que procesos ya fueron atendidos y en qué orden. 
Adicionalmente, el programa debe permitir consultar un proceso especifico de forma inmediata, sin recorrer toda la lista de procesos, y mostrar listados organizados según el estado o prioridad. El sistema también debe incluir la posibilidad de revertir la última acción realizada, como la ejecución o eliminación de un proceso. 
El programa debe mostrar claramente el flujo de ejecución, permitiendo observar cómo los procesos avanzan dentro del sistema. Se debe incluir un menú interactivo y ejemplos de ejecución con varios procesos para evidenciar el correcto manejo de la información. 

## Descripción del Proyecto
Este proyecto implementa un **Gestor de Procesos** en C++ que simula la administración de procesos de un sistema, aplicando estructuras de datos clásicas como:

- **Cola** → procesos pendientes  
- **Lista enlazada** → registro general de procesos  
- **Pila** → deshacer acciones  
- **Tabla Hash** → búsqueda eficiente por ID  

- **Persistencia en archivos CSV** → almacenamiento local  

El sistema permite **registrar, ejecutar, eliminar, deshacer acciones y consultar el historial paso a paso**, asegurando coherencia de estados y evitando operaciones inválidas.

## Estados de un Proceso
Cada proceso puede encontrarse en uno de los siguientes estados:

- `PENDIENTE`
- `EN_EJECUCION`
- `EJECUTADO`
- `ELIMINADO`

Los procesos **eliminados no pueden ejecutarse, buscarse ni eliminarse nuevamente**.

## Persistencia de Datos
Los datos se almacenan en la carpeta **`data/`**:

- `procesos.csv` → estado actual de todos los procesos  
- `historial.csv` → flujo completo de acciones realizadas  

**Los archivos se sobrescriben**, no se duplican registros.