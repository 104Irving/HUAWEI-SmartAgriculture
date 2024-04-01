import router from '@ohos.router'
import axios from '@ohos/axios'

@Entry
@Component
struct Index {
  @State username: string = ''
  @State password: string = ''

  build() {
    Flex({direction:FlexDirection.Column,alignItems:ItemAlign.Center,justifyContent:FlexAlign.SpaceAround}){
      Text('农业灌溉登入端')
        .fontSize(24)
        .fontColor(0xCC6CE7)
        .fontWeight(FontWeight.Bold)

      Column({space:10}){
      TextInput({placeholder:'用户名：'})
        .onChange((value) =>{
          this.username = value
        })
      TextInput({placeholder:'密码：'})
        .type(InputType.Password)
        .onChange((value) =>{
          this.password = value
        })
      Button('登陆')
        .width('95%') .margin({top:10})
        .onClick(() =>{
          axios({
            url:'http://localhost:8080/login',
            params:{
              userName:this.username,
              userPassword:this.password
            }
          }).then(res=>{
            if(res.data===true){
              console.info("噶尼玛的，"+this.username+"进去了！")
              router.pushUrl({
                url:'pages/LoadingPage'
              })
            }else{
              console.info("噶尼玛的，输错了")
            }
          }).catch(error => {
            console.error(error);
          })
        })
      Button('注册') .width('95%')
        .backgroundColor(Color.Gray)
        .margin({top:10})
    }
    .width('90%')
    }
    .width('100%')
    .height('100%')

  }
}