FROM ubuntu:latest
RUN apt-get update && apt-get install -y libstdc++6
#RUN apt-get install -y libboost-all-dev

EXPOSE 8080

WORKDIR /app
#COPY ./build/bin/* /app
COPY ./build/httpsvr/httpsvr /app
COPY ./build/redirector/redirector /app
COPY ./build/redirector/plugins/before/libbefore.so /app
COPY ./build/redirector/plugins/browser/libbrowser.so /app
COPY ./rules.json /app

ENTRYPOINT ["/bin/sh", "-c"]
CMD ["./redirector & ./httpsvr"]
