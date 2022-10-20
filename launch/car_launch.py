from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='firster',
            executable='car_listener',
        ),
        Node(
            package='firster',
            executable='car_start_server',
        )
    ])
