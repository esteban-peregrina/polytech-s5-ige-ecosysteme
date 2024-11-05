FROM ubuntu:24.04

### Image building configuration ###
# === CURRENT BUILDING USER IS ROOT === #

# Define running arguments
ARG USERNAME=esteban
ARG GROUPNAME=$USERNAME
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create a non-root user, a hidden "config" directory, and configure its permission (because we're currently building as root)
RUN groupadd --gid $USER_GID $GROUPNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && mkdir /home/$USERNAME/.config \
    && chown $USER_UID:$USER_GID /home/$USERNAME/.config

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

# Change current working directory to workspace 
WORKDIR /workspace

# Mount all files of the build context inside the current working directory (excluding the ones in .dockerignore)
COPY . .

# Move mounted .bashrc to configure Bash
RUN mv .bashrc /home/$USERNAME/.bashrc

# Configure entrypoint to run at start of the container
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT [ "/bin/bash", "/entrypoint.sh" ]

# Set up default entrypoint passed commands
CMD ["bash"]

#Use "docker build -f .devcontainer/Dockerfile -t  ContaineurExo7 ." inside "Exercice 7"
# USE "chmod +x entrypoint.sh" to set permissions !