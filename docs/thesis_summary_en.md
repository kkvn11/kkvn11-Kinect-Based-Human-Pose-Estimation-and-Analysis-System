# Thesis Summary: Design of a Visual Target Tracking System for Autonomous Vehicles

## 1. Introduction

This thesis presents the design and implementation of a vision-based system for autonomous robot target tracking. The system utilizes Microsoft's Kinect sensor to capture human skeleton data and evaluate fitness movements based on joint angles and bone lengths.

The motivation stems from the need for real-time, non-invasive motion capture in fitness evaluation, where human-machine interaction and feedback play critical roles.

## 2. System Architecture

The proposed system consists of:
- Upper computer (PC-based) for data acquisition and display
- Lower computer (STM32 microcontroller) for pose correction using IMU (MPU6050)
- Kinect sensor for real-time skeleton tracking
- Software interface developed using MFC in C++

## 3. Data Processing Pipeline

1. **Skeleton Extraction**: Using Kinect SDK to obtain 25-joint data
2. **Data Preprocessing**:
   - Interpolation and smoothing
   - Coordinate normalization
   - Angle calculation using joint vectors
3. **Bone Length Estimation**:
   - Polynomial curve fitting with MATLAB
   - Robust filtering based on historical frame statistics
4. **Action Evaluation**:
   - Real-time comparison to predefined motion templates (e.g., squats, back/arm raise)
   - Threshold-based angle deviation analysis

## 4. Software Functionality

- Real-time GUI for user tracking
- Posture calibration interface
- Feedback panel for correctness of motion
- Template management and user customization

## 5. Experimental Results

- High consistency of measured bone lengths compared to manual reference (within ±1cm)
- Accurate discrimination of correct/incorrect fitness actions
- Real-time responsiveness with low latency (<200ms)

## 6. Conclusion

The system provides a low-cost, high-efficiency method for fitness tracking using Kinect and embedded systems. It can be extended for:
- Rehabilitation monitoring
- Home fitness coaching
- Smart gym applications

Future work includes integrating machine learning for automatic action recognition and improving occlusion robustness via multi-camera fusion.

