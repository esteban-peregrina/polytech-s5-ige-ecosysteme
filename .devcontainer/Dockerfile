FROM ubuntu:24.04

### Image building configuration ###
# === CURRENT BUILDING USER IS ROOT === #

# Define running arguments
ARG USERNAME=esteban
ARG USER_ID=1001
ARG GROUPNAME=$USERNAME
ARG GROUP_ID=$USER_ID

# Create a non-root user, a hidden "config" directory, and configure its permission (because we're currently building as root)
RUN groupadd --gid $GROUP_ID $GROUPNAME \
    && useradd -s /bin/bash --uid $USER_ID --gid $GROUP_ID -m $USERNAME \
    && mkdir /home/$USERNAME/.config \
    && chown $USER_ID:$GROUP_ID /home/$USERNAME/.config

# Install necessary packages at build
RUN apt-get update \
    && apt-get install -y \
        gcc \
        g++ \
        make \
        git \
        bash-completion \
    && rm -rf /var/lib/apt/lists/*

# Change current user to $USERNAME
USER $USERNAME

# === CURRENT BUILDING USER IS NOW $USERNAME === #

# Change current working directory to workspace (creates it)
WORKDIR /workspace

# Include .bashrc to configure Bash
COPY .bashrc /home/$USERNAME/.bashrc

# Include and configure entrypoint to run at start of the container
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT [ "/bin/bash", "/entrypoint.sh" ]

# Set up default entrypoint passed commands
CMD ["bash"]

#Use "docker build -f .devcontainer/Dockerfile -t  ContaineurExo7 ." inside "Exercice 7"
# USE "chmod +x entrypoint.sh" to set permissions !