# ComponentUi

Welcome to ComponentUi, a modular UI system developed in C++ using object-oriented programming principles. This project integrates comprehensive interactive elements to facilitate the creation and management of user interfaces.

## Features
- **Modular Design**: Easily add and manage UI components like buttons, panels, and more.
- **Customizable Components**: Each component can be customized and extended to fit specific needs.
- **Interaction Handling**: Built-in support for interactions such as clicks, drags, and zooms using the mouse wheel.
- **Flexible Layout Options**: Arrange components dynamically based on the screen size and other components.

## Project Structure
The project includes various classes that represent UI elements and their behavior:
- **AABBButtonObject**: Handles button functionality with axis-aligned bounding boxes.
- **GraphicsComponent**: Manages the graphical representation of objects.
- **MyTransform**: Provides transformation capabilities (position, rotation, scale) for UI elements.
- **ObjectFactory**: A factory for creating instances of UI objects.

## How It Works
The system utilizes a hierarchical object model where components can contain other components (children). This enables complex layouts and interactions that are easy to manage and update. Each component has its own local transformations which are combined with its parent's transformations to determine its actual position and orientation in the UI.

## Example UI Layout
Below are some screenshots demonstrating the UI components in action:

### Panel and Button Interactions
![Example UI Panel and Button](https://raw.githubusercontent.com/MihneaAndreescu/ComponentUi/main/IMG_1081.jpeg)
"An example of nested panels with buttons dynamically positioned within."

### Dynamic Component Positioning
![Dynamic UI Components](https://raw.githubusercontent.com/MihneaAndreescu/ComponentUi/main/IMG_1082.jpeg)
"UI demonstrating responsive layout and adaptive positioning based on interactions."

### Complex UI Layout
![Complex UI Example](https://raw.githubusercontent.com/MihneaAndreescu/ComponentUi/main/IMG_1083.jpeg)
"Showcase of a complex UI layout with multiple nested components and varied functionality."


