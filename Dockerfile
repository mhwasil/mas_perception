FROM bitbots/bitbots-common:melodic

LABEL maintainer="Argentina Ortega"

WORKDIR /kinetic
COPY mas-perception.rosinstall /melodic

COPY . /kinetic/src/mas_perception

RUN . /opt/ros/mas_stable/setup.sh && \
    apt-get update -qq && \
    rosdep update -q && \
    rosdep install --from-paths src --ignore-src --rosdistro=melodic -y && \
    rm -rf /var/lib/apt/lists/* && \
    catkin config --init && \
    catkin config --extend /opt/ros/mas_stable && \
    catkin config --install --install-space /opt/ros/mas_stable && \
    catkin build && \
    rm -rf /melodic/

WORKDIR /
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["bash"]
