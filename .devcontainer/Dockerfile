FROM espressif/idf:latest


RUN apt-get update && apt-get install -y \
vim \
bash-completion \
&& rm -rf /var/lib/apt/lists/*

RUN echo ". /opt/esp/idf/export.sh" >> /root/.bashrc

WORKDIR /workspaces/esp32_tracing
ENV IDF_TARGET=esp32c6

# Locale settings
ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8   

ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash"]